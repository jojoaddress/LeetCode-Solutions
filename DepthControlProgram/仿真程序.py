"""
三种机具耕深监测仿真验证程序
功能：
- 生成模拟的真实角度（含入土过程、地形起伏、随机噪声）
- 根据几何模型计算理论真值耕深
- 用带噪声的测量值估计耕深（可选卡尔曼滤波）
- 输出误差统计（RMSE, 最大误差）并绘图
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# ================= 1. 机具几何参数（典型值，单位：mm，角度：度） =================
# 深松机
SUBSOILER_PARAMS = {
    "L1": 800.0,  # 下拉杆长度
    "Lt": 400.0,  # 悬挂点至铲尖水平距离
    "Ht": 300.0,  # 悬挂点至铲尖垂直距离（铲尖更低为正）
}

# 旋耕机
ROTARY_TILLER_PARAMS = {"L_arm": 700.0, "R": 250.0}  # 悬挂臂有效长度  # 刀辊半径

# 翻转犁（双倾角简化模型）
PLOUGH_PARAMS = {
    "L_beam": 1000.0,  # 犁梁长度
    "theta_install": 15.0,  # 犁梁初始安装角（度）
}


# ================= 2. 耕深计算函数（真值，无噪声） =================
def depth_subsoiler_true(alpha, beta, params):
    """深松机理论耕深（mm）"""
    L1, Lt, Ht = params["L1"], params["Lt"], params["Ht"]
    delta = np.radians(alpha - beta)
    depth = (L1 + Lt) * np.sin(delta) - Ht * np.cos(delta)
    return np.maximum(0, depth)


def depth_rotary_tiller_true(alpha, beta, params):
    """旋耕机理论耕深（mm）"""
    L_arm, R = params["L_arm"], params["R"]
    delta = np.radians(alpha - beta)
    depth = L_arm * np.sin(delta) + R
    return np.maximum(0, depth)


def depth_plough_true(alpha, beta, params):
    """翻转犁理论耕深（mm）"""
    L_beam, theta_install = params["L_beam"], params["theta_install"]
    delta = np.radians(alpha - beta + theta_install)
    depth = L_beam * np.sin(delta)
    return np.maximum(0, depth)


# 统一的真值计算接口
def true_depth(tool_type, alpha, beta, params):
    if tool_type == "subsoiler":
        return depth_subsoiler_true(alpha, beta, params)
    elif tool_type == "rotary_tiller":
        return depth_rotary_tiller_true(alpha, beta, params)
    elif tool_type == "plough":
        return depth_plough_true(alpha, beta, params)
    else:
        raise ValueError("Unknown tool type")


# ================= 3. 估计耕深（用带噪声的测量角度） =================
# 注意：估计函数与真值函数形式完全相同，只是输入角度有噪声
# 为方便，直接复用真值函数，但输入带噪声的角度
def estimated_depth(tool_type, alpha_meas, beta_meas, params):
    return true_depth(tool_type, alpha_meas, beta_meas, params)


# ================= 4. 一维卡尔曼滤波器（平滑深度序列） =================
class KalmanFilter1D:
    def __init__(self, Q=0.01, R=0.1, init_x=0):
        self.Q = Q  # 过程噪声协方差
        self.R = R  # 测量噪声协方差
        self.x = init_x  # 状态估计
        self.P = 1.0  # 估计误差协方差

    def update(self, z):
        # 预测
        self.P = self.P + self.Q
        # 更新
        K = self.P / (self.P + self.R)
        self.x = self.x + K * (z - self.x)
        self.P = (1 - K) * self.P
        return self.x


# ================= 5. 生成模拟工况数据 =================
def generate_simulation_data(duration=30, fs=40):
    """
    生成模拟的“真实”角度及含噪声的测量角度
    duration: 秒
    fs: 采样率 Hz
    返回: t, alpha_true, beta_true, alpha_meas, beta_meas
    """
    t = np.linspace(0, duration, int(duration * fs))

    # ----- 真实下拉杆/机具角度 alpha_true (度) -----
    # 模拟：提升(-10°) -> 快速入土至20° -> 作业中正弦波动 -> 出土
    alpha_true = np.zeros_like(t)
    for i, ti in enumerate(t):
        if ti < 3:
            alpha_true[i] = -10  # 初始提升
        elif ti < 8:
            # 入土过程：-10° -> 22°
            alpha_true[i] = -10 + (ti - 3) / 5 * 32
        elif ti < 25:
            # 稳定作业：22° 基础上叠加小幅波动
            alpha_true[i] = (
                22
                + 1.5 * np.sin(2 * np.pi * 0.3 * (ti - 8))
                + 0.5 * np.sin(2 * np.pi * 1.2 * (ti - 8))
            )
        else:
            # 出土：22° -> -10°
            alpha_true[i] = 22 - (ti - 25) / 5 * 32
            if alpha_true[i] < -10:
                alpha_true[i] = -10
    # 限制范围
    alpha_true = np.clip(alpha_true, -15, 30)

    # ----- 真实车身倾角 beta_true (度) 模拟坡地及起伏 -----
    beta_true = 2.0 * np.sin(2 * np.pi * 0.1 * t) + 0.8 * np.sin(2 * np.pi * 0.5 * t)

    # ----- 添加传感器噪声（标准差0.2°，模拟实际倾角传感器精度）-----
    noise_std = 0.2  # 度
    alpha_meas = alpha_true + np.random.normal(0, noise_std, len(t))
    beta_meas = beta_true + np.random.normal(0, noise_std, len(t))

    return t, alpha_true, beta_true, alpha_meas, beta_meas


# ================= 6. 主仿真流程 =================
def run_simulation(tool_type, params, use_kalman=False, duration=30, fs=40):
    # 生成数据
    t, alpha_true, beta_true, alpha_meas, beta_meas = generate_simulation_data(
        duration, fs
    )

    # 真值耕深
    depth_true = true_depth(tool_type, alpha_true, beta_true, params)

    # 直接估计耕深（无滤波）
    depth_est_raw = estimated_depth(tool_type, alpha_meas, beta_meas, params)

    # 可选：卡尔曼滤波后估计
    if use_kalman:
        kf = KalmanFilter1D(Q=0.5, R=2.0, init_x=depth_est_raw[0])
        depth_est_filtered = np.zeros_like(depth_est_raw)
        for i, z in enumerate(depth_est_raw):
            depth_est_filtered[i] = kf.update(z)
        depth_est = depth_est_filtered
    else:
        depth_est = depth_est_raw

    # 误差计算
    error = depth_est - depth_true
    rmse = np.sqrt(np.mean(error**2))
    max_abs_error = np.max(np.abs(error))
    percent_within_10mm = np.mean(np.abs(error) <= 10) * 100

    # 打印统计
    print(f"\n========== {tool_type.upper()} 仿真结果 ==========")
    print(f"RMSE: {rmse:.2f} mm")
    print(f"最大绝对误差: {max_abs_error:.2f} mm")
    print(f"误差 ≤ 10mm 的比例: {percent_within_10mm:.1f}%")
    if use_kalman:
        print("已启用卡尔曼滤波")
    else:
        print("未启用卡尔曼滤波")

    # 绘图
    fig, axes = plt.subplots(4, 1, figsize=(12, 10), sharex=True)

    # 角度曲线
    axes[0].plot(t, alpha_true, "b-", label="True α (机具)", linewidth=1.5)
    axes[0].plot(
        t, alpha_meas, "r.", markersize=1, label="Measured α (noisy)", alpha=0.5
    )
    axes[0].plot(t, beta_true, "g-", label="True β (车身)", linewidth=1.5)
    axes[0].set_ylabel("Angle (deg)")
    axes[0].legend(loc="upper right")
    axes[0].grid(True)
    axes[0].set_title(f"{tool_type} - Angle Simulation")

    # 耕深真值 vs 估计值
    axes[1].plot(t, depth_true, "k-", label="True depth", linewidth=2)
    axes[1].plot(t, depth_est, "r--", label="Estimated depth", linewidth=1)
    axes[1].set_ylabel("Depth (mm)")
    axes[1].legend()
    axes[1].grid(True)

    # 误差曲线
    axes[2].plot(t, error, "b-", linewidth=0.8)
    axes[2].axhline(y=10, color="r", linestyle="--", label="+10 mm")
    axes[2].axhline(y=-10, color="r", linestyle="--", label="-10 mm")
    axes[2].set_ylabel("Error (mm)")
    axes[2].set_ylim(-30, 30)
    axes[2].legend()
    axes[2].grid(True)

    # 误差分布直方图
    axes[3].hist(error, bins=50, density=True, alpha=0.7, color="c")
    axes[3].axvline(x=0, color="k", linestyle="-")
    axes[3].set_xlabel("Error (mm)")
    axes[3].set_ylabel("Density")
    axes[3].set_title(f"Error distribution (RMSE={rmse:.1f}mm)")
    axes[3].grid(True)

    plt.tight_layout()
    plt.show()

    return rmse, max_abs_error, percent_within_10mm


# ================= 7. 运行所有机具的仿真 =================
if __name__ == "__main__":
    # 深松机
    run_simulation("subsoiler", SUBSOILER_PARAMS, use_kalman=False)
    run_simulation("subsoiler", SUBSOILER_PARAMS, use_kalman=True)

    # 旋耕机
    run_simulation("rotary_tiller", ROTARY_TILLER_PARAMS, use_kalman=False)
    run_simulation("rotary_tiller", ROTARY_TILLER_PARAMS, use_kalman=True)

    # 翻转犁
    run_simulation("plough", PLOUGH_PARAMS, use_kalman=False)
    run_simulation("plough", PLOUGH_PARAMS, use_kalman=True)
