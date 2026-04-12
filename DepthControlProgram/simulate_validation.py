import math
import numpy as np
import matplotlib.pyplot as plt
from abc import ABC, abstractmethod
from typing import List, Tuple, Dict, Any

plt.rcParams["font.sans-serif"] = [
    "SimHei",
    "Microsoft YaHei",
    "WenQuanYi Micro Hei",
    "DejaVu Sans",
]
plt.rcParams["axes.unicode_minus"] = False  # 解决负号显示问题


# ======================= 1. 地形与车身模型 =======================
class TerrainModel:
    """生成地形剖面并计算车身俯仰角（假设拖拉机始终贴合地面）"""

    def __init__(
        self,
        length: float = 100.0,
        resolution: float = 0.2,
        wave_amplitude: float = 0.05,
        wave_period: float = 10.0,
        random_roughness: float = 0.01,
    ):
        """
        :param length:       作业距离（米）
        :param resolution:   采样间距（米）
        :param wave_amplitude: 正弦波幅值（米）
        :param wave_period:   正弦波周期（米）
        :param random_roughness: 随机噪声标准差（米）
        """
        self.x = np.arange(0, length, resolution)
        # 地形高度 = 正弦波 + 随机噪声
        self.elevation = wave_amplitude * np.sin(
            2 * np.pi * self.x / wave_period
        ) + np.random.normal(0, random_roughness, len(self.x))
        # 计算坡度（弧度）-> 车身俯仰角（度）
        dx = resolution
        dy = np.gradient(self.elevation, dx)
        self.slope_rad = np.arctan(dy)
        self.beta_deg = np.degrees(self.slope_rad)  # 车身俯仰角 β

    def get_beta(self, index: int) -> float:
        return self.beta_deg[index]


# ======================= 2. 悬挂控制器（模拟机具调节）=======================
class SuspensionController:
    """简单比例控制器，使耕深跟踪目标值，输出机具相对于车身的转角 delta = α - β"""

    def __init__(self, Kp: float = 0.5, target_depth_mm: float = 200.0):
        self.Kp = Kp
        self.target_depth = target_depth_mm
        self.integral = 0.0

    def compute_delta(self, current_depth_mm: float, dt: float) -> float:
        """根据深度误差计算需要的相对角度变化（度）"""
        error = self.target_depth - current_depth_mm
        # 比例控制，输出角度调整量（度），限制范围防止过大
        delta_change = self.Kp * error
        delta_change = np.clip(delta_change, -5.0, 5.0)
        # 这里简化：返回调整后的相对角度（实际应累加，但为简单直接返回）
        # 更真实的模型需要状态保持，但为仿真合理，我们直接返回比例结果
        return delta_change


# ======================= 3. 机具计算器抽象基类 =======================
class ImplementCalculator(ABC):
    @abstractmethod
    def calculate_depth(
        self, alpha_deg: float, beta_deg: float, alpha0_deg: float, beta0_deg: float
    ) -> float:
        """返回耕深（毫米）"""
        pass

    @abstractmethod
    def get_characteristic_length(self) -> float:
        """返回特征长度（mm），用于控制器初始估算"""
        pass


# 具体机具实现
class SubsoilerCalculator(ImplementCalculator):
    def __init__(
        self,
        L1: float,
        Lt: float,
        Ht: float,
        install_angle: float = 0.0,
        calibration: float = 1.0,
        zero_offset: float = 0.0,
    ):
        self.L1 = L1
        self.Lt = Lt
        self.Ht = Ht
        self.install_angle = install_angle
        self.calibration = calibration
        self.zero_offset = zero_offset

    def calculate_depth(
        self, alpha_deg: float, beta_deg: float, alpha0_deg: float, beta0_deg: float
    ) -> float:
        delta = (alpha_deg - alpha0_deg) - (beta_deg - beta0_deg) + self.install_angle
        rad = math.radians(delta)
        raw = (self.L1 + self.Lt) * math.sin(rad) - self.Ht * math.cos(rad)
        return max(0.0, raw * self.calibration - self.zero_offset)

    def get_characteristic_length(self) -> float:
        return self.L1 + self.Lt


class RotaryTillerCalculator(ImplementCalculator):
    def __init__(
        self,
        Larm: float,
        R: float,
        install_angle: float = 0.0,
        calibration: float = 1.0,
        zero_offset: float = 0.0,
    ):
        self.Larm = Larm
        self.R = R
        self.install_angle = install_angle
        self.calibration = calibration
        self.zero_offset = zero_offset

    def calculate_depth(
        self, alpha_deg: float, beta_deg: float, alpha0_deg: float, beta0_deg: float
    ) -> float:
        delta = (alpha_deg - alpha0_deg) - (beta_deg - beta0_deg) + self.install_angle
        rad = math.radians(delta)
        raw = self.Larm * math.sin(rad) + self.R
        return max(0.0, raw * self.calibration - self.zero_offset)

    def get_characteristic_length(self) -> float:
        return self.Larm


class PloughCalculator(ImplementCalculator):
    def __init__(
        self,
        Lbeam: float,
        theta_install: float,
        install_angle: float = 0.0,
        calibration: float = 1.0,
        zero_offset: float = 0.0,
    ):
        self.Lbeam = Lbeam
        self.theta_install = theta_install
        self.install_angle = install_angle
        self.calibration = calibration
        self.zero_offset = zero_offset

    def calculate_depth(
        self, alpha_deg: float, beta_deg: float, alpha0_deg: float, beta0_deg: float
    ) -> float:
        delta = (
            (alpha_deg - alpha0_deg)
            - (beta_deg - beta0_deg)
            + self.theta_install
            + self.install_angle
        )
        rad = math.radians(delta)
        raw = self.Lbeam * math.sin(rad)
        return max(0.0, raw * self.calibration - self.zero_offset)

    def get_characteristic_length(self) -> float:
        return self.Lbeam


# ======================= 4. 仿真与验证引擎 =======================
class SimulationValidator:
    def __init__(
        self,
        implement: ImplementCalculator,
        terrain: TerrainModel,
        alpha0_deg: float = 0.0,
        beta0_deg: float = 0.0,
        target_depth_mm: float = 200.0,
        add_sensor_noise_std: float = 0.5,
    ):
        """
        :param implement: 机具计算器实例
        :param terrain: 地形模型实例
        :param alpha0_deg: 机具初始角度（度）
        :param beta0_deg: 车身初始角度（度）
        :param target_depth_mm: 目标耕深（毫米）
        :param add_sensor_noise_std: 倾角传感器噪声标准差（度）
        """
        self.impl = implement
        self.terrain = terrain
        self.alpha0 = alpha0_deg
        self.beta0 = beta0_deg
        self.target_depth = target_depth_mm
        self.noise_std = add_sensor_noise_std

    def run_simulation(self) -> Tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
        """
        执行仿真，返回:
            x: 距离（米）
            beta_meas: 测量的车身俯仰角（度，含噪声）
            alpha_meas: 测量的机具角（度，含噪声）
            depth_calc: 由机具公式计算出的耕深（毫米）
        """
        n = len(self.terrain.x)
        beta_true = self.terrain.beta_deg
        # 初始化机具角 alpha_true（初始等于 alpha0）
        alpha_true = np.full(n, self.alpha0, dtype=float)
        # 模拟闭环控制：每个采样点根据上一深度调整 alpha
        # 使用简单比例控制
        Kp = 0.3  # 控制增益，度/mm
        for i in range(1, n):
            # 获取上一位置的深度
            depth_prev = self.impl.calculate_depth(
                alpha_true[i - 1], beta_true[i - 1], self.alpha0, self.beta0
            )
            error = self.target_depth - depth_prev
            # 调整 alpha 相对于 beta 的变化量
            delta_alpha = Kp * error
            # 限制单步调整幅度
            delta_alpha = np.clip(delta_alpha, -2.0, 2.0)
            # 同时考虑地形变化影响（保持机具相对地面角度基本恒定）
            # 这里简单地将 alpha 设为上一值加上调整量
            alpha_true[i] = alpha_true[i - 1] + delta_alpha
            # 可选：加入随机扰动模拟液压响应
            alpha_true[i] += np.random.normal(0, 0.2)

        # 添加传感器噪声
        beta_meas = beta_true + np.random.normal(0, self.noise_std, n)
        alpha_meas = alpha_true + np.random.normal(0, self.noise_std, n)

        # 计算耕深
        depth_calc = np.array(
            [
                self.impl.calculate_depth(
                    alpha_meas[i], beta_meas[i], self.alpha0, self.beta0
                )
                for i in range(n)
            ]
        )
        return self.terrain.x, beta_meas, alpha_meas, depth_calc

    def evaluate(self, plot: bool = True) -> Dict[str, float]:
        """运行仿真并评估精度指标"""
        x, beta, alpha, depth = self.run_simulation()
        # 理论期望深度：目标深度加上地形影响导致的偏差？实际上悬挂控制会尽量维持深度稳定，
        # 所以期望深度应为目标深度附近。这里我们简单以目标深度为基准计算误差。
        error = depth - self.target_depth
        mae = np.mean(np.abs(error))
        rmse = np.sqrt(np.mean(error**2))
        max_err = np.max(np.abs(error))
        print(f"\n仿真评估结果（目标深度 = {self.target_depth} mm）")
        print(f"  平均绝对误差 MAE: {mae:.2f} mm")
        print(f"  均方根误差 RMSE: {rmse:.2f} mm")
        print(f"  最大绝对误差: {max_err:.2f} mm")

        if plot:
            plt.figure(figsize=(12, 8))
            plt.subplot(3, 1, 1)
            plt.plot(x, beta, label="车身俯仰角 β (含噪声)")
            plt.plot(x, alpha, label="机具角 α (含噪声)")
            plt.ylabel("角度 (度)")
            plt.legend()
            plt.grid(True)

            plt.subplot(3, 1, 2)
            plt.plot(x, depth, label="计算耕深")
            plt.axhline(self.target_depth, color="r", linestyle="--", label="目标深度")
            plt.ylabel("耕深 (mm)")
            plt.legend()
            plt.grid(True)

            plt.subplot(3, 1, 3)
            plt.plot(x, error, label="误差")
            plt.xlabel("距离 (m)")
            plt.ylabel("误差 (mm)")
            plt.legend()
            plt.grid(True)
            plt.tight_layout()
            plt.show()

        return {"MAE": mae, "RMSE": rmse, "MaxError": max_err}


# ======================= 5. 主测试函数 =======================
def main():
    # 设置随机种子以便复现
    np.random.seed(42)

    # 创建地形（长度100米，分辨率0.2米，起伏适中）
    terrain = TerrainModel(
        length=100.0,
        resolution=0.2,
        wave_amplitude=0.08,
        wave_period=15.0,
        random_roughness=0.005,
    )

    # 定义各机具的参数（单位：毫米，角度）
    implements = {
        "深松机": SubsoilerCalculator(L1=1280, Lt=680, Ht=450, install_angle=0.0),
        "旋耕机": RotaryTillerCalculator(Larm=800, R=250, install_angle=0.0),
        "翻转犁": PloughCalculator(Lbeam=1200, theta_install=15.0, install_angle=0.0),
    }

    # 对每个机具进行仿真验证
    for name, impl in implements.items():
        print(f"\n{'='*50}\n正在验证: {name}\n{'='*50}")
        validator = SimulationValidator(
            implement=impl,
            terrain=terrain,
            alpha0_deg=0.0,
            beta0_deg=0.0,
            target_depth_mm=200.0,
            add_sensor_noise_std=0.3,  # 模拟传感器噪声
        )
        metrics = validator.evaluate(plot=True)
        # 可选：打印特征长度
        print(f"特征长度: {impl.get_characteristic_length()} mm")


if __name__ == "__main__":
    main()
