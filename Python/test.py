import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Rectangle, FancyBboxPatch
import matplotlib.patches as mpatches

# 设置中文字体
plt.rcParams['font.size'] = 12

# 创建图形 - 三行一列布局，模仿原图的三个子图
fig, axes = plt.subplots(3, 1, figsize=(14, 12))
fig.patch.set_facecolor('white')

# ========== 子图1: 耕深随时间变化 ==========
ax1 = axes[0]
ax1.set_facecolor('white')

# 生成时间序列数据（1小时）
t = np.linspace(0, 1, 5000)  # 1小时，高频采样
target_depth = 20.0  # 目标耕深20cm

# 模拟实际耕深：增加更多波动，使稳定性曲线更真实
np.random.seed(42)

# 低频趋势（土壤变化、坡度）
low_freq = 0.6 * np.sin(2 * np.pi * 0.3 * t) + 0.3 * np.sin(2 * np.pi * 0.7 * t)

# 中频波动（地形起伏）
mid_freq = 0.4 * np.sin(2 * np.pi * 2.0 * t) + 0.2 * np.sin(2 * np.pi * 4.0 * t)

# 高频噪声（传感器噪声）
noise = 0.25 * np.random.randn(len(t))

# 偶发尖峰（石块、土壤突变）—— 随机位置增加偏离
spikes = np.zeros_like(t)
spike_indices = np.random.choice(len(t), size=15, replace=False)
for idx in spike_indices:
    spikes[idx] = np.random.choice([-1.2, 1.2])  # 突发±1.2cm偏离

# 合成实际耕深
actual_depth = target_depth + low_freq + mid_freq + noise + spikes

# 对尖峰进行平滑（避免过于突兀，但保留明显波动）
actual_depth = actual_depth + 0.1 * np.sin(2 * np.pi * 10 * t)  # 微调高频

# 绘制目标线
ax1.axhline(y=target_depth, color='red', linestyle='--', linewidth=1.5, label='目标耕深 (cm)')

# 绘制实际耕深
ax1.plot(t, actual_depth, color='blue', linewidth=0.8, alpha=0.9, label='实际耕深 (cm)')

# 绘制±1cm容差带
ax1.axhspan(target_depth-1, target_depth+1, alpha=0.15, color='green', label='±1cm容差带')

# 设置坐标轴
ax1.set_xlim(0, 1)
ax1.set_ylim(17.5, 22.5)
ax1.set_ylabel('耕深 (cm)', fontsize=12)
ax1.set_xticks(np.arange(0, 1.1, 0.2))
ax1.set_xticklabels(['0.0', '0.2', '0.4', '0.6', '0.8', '1.0'])
ax1.set_yticks([18, 19, 20, 21, 22])
ax1.grid(True, linestyle='--', alpha=0.4)
ax1.legend(loc='lower left', fontsize=9, framealpha=0.9)

# 添加标题
ax1.set_title('旋耕机耕深仿真（目标：20.0cm）', fontsize=14, fontweight='bold', pad=15)

# ========== 子图2: 稳定性占比随时间变化（增强波动） ==========
ax2 = axes[1]
ax2.set_facecolor('white')

# 计算稳定性（在容差带内的比例），使用滑动窗口（缩小窗口以增加波动）
window_size = 200  # 从500减小到200，提高响应速度
stability_ratio = []
t_window = []

for i in range(window_size, len(t), 50):
    window_data = actual_depth[i-window_size:i]
    in_tolerance = np.sum((window_data >= target_depth-1) & (window_data <= target_depth+1))
    ratio = (in_tolerance / window_size) * 100
    stability_ratio.append(ratio)
    t_window.append(t[i])

stability_ratio = np.array(stability_ratio)

# 绘制稳定性曲线
ax2.fill_between(t_window, 80, stability_ratio, where=(stability_ratio >= 80), 
                  alpha=0.3, color='green', interpolate=True)
ax2.fill_between(t_window, stability_ratio, 100, where=(stability_ratio < 100), 
                  alpha=0.3, color='orange', interpolate=True)
ax2.plot(t_window, stability_ratio, color='orange', linewidth=1.5, label='实时稳定性')

# 绘制参考线
ax2.axhline(y=85, color='red', linestyle='--', linewidth=1.5, label='85%要求线')
ax2.axhline(y=90, color='blue', linestyle=':', linewidth=1.5, label='90%参考线')
ax2.axhline(y=95, color='green', linestyle=':', linewidth=1.5, label='95%优秀线')

# 添加稳定性达标区域标注
ax2.axhspan(85, 100, alpha=0.1, color='green', label='稳定性达标区域')

# 计算并显示平均稳定性
avg_stability = np.mean(stability_ratio)
ax2.text(0.02, 82, f'平均稳定性: {avg_stability:.2f}%', fontsize=10, 
         bbox=dict(boxstyle='round,pad=0.3', facecolor='yellow', alpha=0.7))

# 设置坐标轴
ax2.set_xlim(0, 1)
ax2.set_ylim(70, 100)  # 放宽下限以容纳波动
ax2.set_ylabel('稳定性占比 (%)', fontsize=12)
ax2.set_xlabel('时间 (h)', fontsize=12)
ax2.set_xticks(np.arange(0, 1.1, 0.2))
ax2.set_xticklabels(['0.0', '0.2', '0.4', '0.6', '0.8', '1.0'])
ax2.set_yticks(np.arange(70, 101, 5))
ax2.grid(True, linestyle='--', alpha=0.4)
ax2.legend(loc='lower right', fontsize=9, framealpha=0.9)

# ========== 子图3: 耕深误差直方图 ==========
ax3 = axes[2]
ax3.set_facecolor('white')

# 计算误差
depth_error = actual_depth - target_depth

# 绘制直方图
n, bins, patches = ax3.hist(depth_error, bins=50, color='gray', edgecolor='black', alpha=0.7)

# 添加统计信息文本
max_error = np.max(depth_error)
min_error = np.min(depth_error)
mean_error = np.mean(depth_error)
std_error = np.std(depth_error)

# 在左上角添加统计信息框
textstr = f'最大误差: +{max_error:.2f}cm\n最小误差: {min_error:.2f}cm\n均值: {mean_error:.3f}cm\n标准差: {std_error:.3f}cm'
props = dict(boxstyle='round,pad=0.5', facecolor='white', alpha=0.9, edgecolor='gray')
ax3.text(0.02, 0.98, textstr, transform=ax3.transAxes, fontsize=10,
         verticalalignment='top', bbox=props)

# 绘制参考线
ax3.axvline(x=0, color='red', linestyle='--', linewidth=1.5, label='无误差点')
ax3.axvline(x=1, color='green', linestyle=':', linewidth=1.5, alpha=0.7, label='+1cm误差线')
ax3.axvline(x=-1, color='green', linestyle=':', linewidth=1.5, alpha=0.7, label='-1cm误差线')

# 设置坐标轴
ax3.set_xlim(-1.8, 1.8)  # 扩大范围以容纳更大误差
ax3.set_ylim(0, max(n) * 1.15)
ax3.set_xlabel('耕深误差 (cm)', fontsize=12)
ax3.set_ylabel('频次', fontsize=12)
ax3.grid(True, linestyle='--', alpha=0.4, axis='y')
ax3.legend(loc='upper right', fontsize=9, framealpha=0.9)

# 调整布局
plt.tight_layout()
plt.subplots_adjust(hspace=0.35)

# 保存
plt.savefig('/mnt/kimi/output/tillage_depth_simulation.png', dpi=300, bbox_inches='tight', 
            facecolor='white', edgecolor='none')
plt.show()

print("✅ 图表已生成！")