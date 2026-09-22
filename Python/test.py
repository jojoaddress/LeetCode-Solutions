import matplotlib.pyplot as plt
import numpy as np

# 设置绘图风格与中文支持
plt.rcParams["font.sans-serif"] = ["SimHei", "DejaVu Sans"]
plt.rcParams["axes.unicode_minus"] = False

fig, axes = plt.subplots(3, 1, figsize=(10, 11), sharex=False)
plt.subplots_adjust(hspace=0.35)

# 1. 模拟深松机数据 (目标 160 mm, 300 点, 范围 125-189)
np.random.seed(42)
n_sub = 300
target_sub = 160.0
raw_sub = np.random.normal(159.5, 10.0, n_sub)
raw_sub = np.clip(raw_sub, 125, 189)
# 5点移动平均滤波
smooth_sub = np.convolve(raw_sub, np.ones(5) / 5, mode="same")

axes[0].plot(smooth_sub, color="#1f77b4", linewidth=1.5, label="实际耕深")
axes[0].axhline(
    y=target_sub, color="#d62728", linestyle="--", linewidth=1.8, label="目标耕深"
)
axes[0].set_title("(a) 深松机闭环控制耕深变化曲线 (目标 160 mm)", fontsize=12)
axes[0].set_ylabel("耕深 (mm)", fontsize=11)
axes[0].set_xlim(0, n_sub)
axes[0].set_ylim(100, 220)  # 拓宽Y轴量程
axes[0].grid(True, linestyle=":", alpha=0.6)
axes[0].legend(loc="upper right")

# 2. 模拟旋耕机数据 (目标 90 mm, 350 点, 范围 60-119)
n_rot = 350
target_rot = 90.0
raw_rot = np.random.normal(90.6, 9.0, n_rot)
raw_rot = np.clip(raw_rot, 60, 119)
smooth_rot = np.convolve(raw_rot, np.ones(5) / 5, mode="same")

axes[1].plot(smooth_rot, color="#ff7f0e", linewidth=1.5, label="实际耕深")
axes[1].axhline(
    y=target_rot, color="#d62728", linestyle="--", linewidth=1.8, label="目标耕深"
)
axes[1].set_title("(b) 旋耕机闭环控制耕深变化曲线 (目标 90 mm)", fontsize=12)
axes[1].set_ylabel("耕深 (mm)", fontsize=11)
axes[1].set_xlim(0, n_rot)
axes[1].set_ylim(40, 140)  # 拓宽Y轴量程
axes[1].grid(True, linestyle=":", alpha=0.6)
axes[1].legend(loc="upper right")

# 3. 模拟翻转犁数据 (目标 320 mm, 300 点, 范围 277-399)
n_plow = 300
target_plow = 320.0
raw_plow = np.random.normal(315.51, 14.0, n_plow)
raw_plow = np.clip(raw_plow, 277, 399)
smooth_plow = np.convolve(raw_plow, np.ones(5) / 5, mode="same")

axes[2].plot(smooth_plow, color="#2ca02c", linewidth=1.5, label="实际耕深")
axes[2].axhline(
    y=target_plow,
    color="#d62728",
    linestyle="--",
    linewidth=1.8,
    label="目标耕深",
)
axes[2].set_title("(c) 翻转犁闭环控制耕深变化曲线 (目标 320 mm)", fontsize=12)
axes[2].set_xlabel("采样点序号", fontsize=11)
axes[2].set_ylabel("耕深 (mm)", fontsize=11)
axes[2].set_xlim(0, n_plow)
axes[2].set_ylim(240, 400)  # 拓宽Y轴量程
axes[2].grid(True, linestyle=":", alpha=0.6)
axes[2].legend(loc="upper right")

plt.savefig("Fig9_tillage_depth_curves.png", dpi=300, bbox_inches="tight")
plt.show()