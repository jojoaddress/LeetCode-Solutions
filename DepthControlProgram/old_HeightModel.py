"""
三点悬挂高度自适应模型
输入特征: [深度, 硬度, 速度, 坡度X, 坡度Y, 深度×硬度]
输出: 三点悬挂高度 (mm)
采用递推最小二乘(RLS)在线更新，支持多机具独立模型
"""

import numpy as np


class RidgeRLSHeightModel:
    """单个机具的Ridge回归 + RLS更新模型"""

    def __init__(
        self,
        tool_type: str,
        forget_factor: float = 0.98,
        delta: float = 100.0,
        ridge_penalty: float = 1e-4,
    ):
        """
        :param tool_type:     机具标识
        :param forget_factor: 遗忘因子 λ (0.95~1.0)
        :param delta:         P矩阵初始对角值（大数表示初始不确定）
        :param ridge_penalty: 正则项系数（防止P矩阵奇异）
        """
        self.tool_type = tool_type
        self.lambda_ = forget_factor
        self.ridge_penalty = ridge_penalty

        # 特征维度：偏置 + 深度 + 硬度 + 速度 + 坡度X + 坡度Y + 深度×硬度
        self.dim = 7
        # 初始化参数 θ
        self.theta = np.zeros(self.dim)
        # 初始化协方差矩阵 P = δ * I
        self.P = np.eye(self.dim) * delta

    def _construct_features(
        self,
        depth_mm: float,
        hardness_mpa: float,
        speed_kph: float,
        slope_x_deg: float,
        slope_y_deg: float,
    ) -> np.ndarray:
        """构造特征向量: [1, d, h, v, sx, sy, d*h]"""
        return np.array(
            [
                1.0,
                depth_mm,
                hardness_mpa,
                speed_kph,
                slope_x_deg,
                slope_y_deg,
                depth_mm * hardness_mpa,
            ]
        )

    def predict(
        self,
        depth_mm: float,
        hardness_mpa: float,
        speed_kph: float,
        slope_x_deg: float,
        slope_y_deg: float,
    ) -> float:
        """预测高度（mm）"""
        x = self._construct_features(
            depth_mm, hardness_mpa, speed_kph, slope_x_deg, slope_y_deg
        )
        height = np.dot(self.theta, x)
        # 限幅到安全范围 [0, 600] mm
        return max(0.0, min(600.0, height))

    def update(
        self,
        depth_mm: float,
        hardness_mpa: float,
        speed_kph: float,
        slope_x_deg: float,
        slope_y_deg: float,
        actual_height_mm: float,
    ):
        """在线更新模型参数（RLS递推）"""
        x = self._construct_features(
            depth_mm, hardness_mpa, speed_kph, slope_x_deg, slope_y_deg
        )
        # 预测值
        pred = np.dot(self.theta, x)
        # 误差
        error = actual_height_mm - pred

        # 增益向量 k = P x / (λ + xᵀ P x)
        Px = self.P @ x
        denom = self.lambda_ + np.dot(x, Px)
        k = Px / denom

        # 更新参数
        self.theta += k * error

        # 更新协方差矩阵 P = (I - k xᵀ) P / λ + 正则项保证稳定
        I = np.eye(self.dim)
        self.P = (I - np.outer(k, x)) @ self.P / self.lambda_
        # 添加小正则项防止奇异
        self.P += self.ridge_penalty * np.eye(self.dim)

    def get_params(self):
        """返回当前参数副本（用于持久化）"""
        return self.theta.copy()

    def set_params(self, theta: np.ndarray):
        """手动设置参数（用于恢复保存的模型）"""
        if theta.shape == (self.dim,):
            self.theta = theta.copy()


class MultiToolHeightModel:
    """管理多种机具的RLS模型容器"""

    def __init__(self, forget_factor=0.98, delta=100.0, ridge_penalty=1e-4):
        self.models = {}
        self.default_forget = forget_factor
        self.default_delta = delta
        self.default_ridge = ridge_penalty

    def get_model(self, tool_type: str):
        """获取或创建指定机具的模型"""
        if tool_type not in self.models:
            self.models[tool_type] = RidgeRLSHeightModel(
                tool_type, self.default_forget, self.default_delta, self.default_ridge
            )
        return self.models[tool_type]

    def predict(
        self,
        tool_type: str,
        depth_mm: float,
        hardness_mpa: float,
        speed_kph: float,
        slope_x_deg: float,
        slope_y_deg: float,
    ) -> float:
        """预测高度"""
        model = self.get_model(tool_type)
        return model.predict(
            depth_mm, hardness_mpa, speed_kph, slope_x_deg, slope_y_deg
        )

    def update(
        self,
        tool_type: str,
        depth_mm: float,
        hardness_mpa: float,
        speed_kph: float,
        slope_x_deg: float,
        slope_y_deg: float,
        actual_height_mm: float,
    ):
        """在线更新模型"""
        model = self.get_model(tool_type)
        model.update(
            depth_mm,
            hardness_mpa,
            speed_kph,
            slope_x_deg,
            slope_y_deg,
            actual_height_mm,
        )

    def save_models(self, save_dir="."):
        """保存所有模型参数到文件（可选）"""
        import os

        np.savez(
            os.path.join(save_dir, "height_models.npz"),
            **{f"{t}_theta": m.get_params() for t, m in self.models.items()},
        )

    def load_models(self, filepath):
        """从文件加载模型参数"""
        data = np.load(filepath)
        for key in data.files:
            if key.endswith("_theta"):
                tool = key[:-6]  # 去掉 "_theta"
                theta = data[key]
                model = self.get_model(tool)
                model.set_params(theta)
