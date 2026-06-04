import pandas as pd
import numpy as np

np.random.seed(42)

# ==================== 参数配置 ====================
n_points = 300
base_depth = 100
normal_std = 2.0
jump_std = 12.0
jump_prob = 0.05
stability_decay = 0.9
random_scale = 1.5

# 候选测试值（整十数，可根据需要调整范围）
candidate_test_values = [300, 310, 320, 330, 340]

# ==================== 1. 生成深度序列 (整数) ====================
depths = [base_depth]
for _ in range(n_points - 1):
    if np.random.random() < jump_prob:
        step = np.random.normal(0, jump_std)
    else:
        step = np.random.normal(0, normal_std)
    new_depth = depths[-1] + step
    new_depth = np.clip(new_depth, 300, 340)
    depths.append(new_depth)

depths_int = np.round(depths).astype(int)

# ==================== 2. 生成稳定性百分比 ====================
stabilities = []
for i, d in enumerate(depths_int):
    if i == 0:
        base_stab = 95.0
    else:
        delta = abs(d - depths_int[i - 1])
        base_stab = 100 - stability_decay * delta
    noise = np.random.uniform(-random_scale, random_scale)
    stab = base_stab + noise
    stab = np.clip(stab, 60, 100)
    stabilities.append(stab)

stabs_rounded = np.round(stabilities, 1)
stabs_with_percent = [f"{s}%" for s in stabs_rounded]

# ==================== 3. 生成测试值列 (整十数，与深度相差≥10，每10行填一次) ====================
test_values = []
for i, d in enumerate(depths_int):
    # i 从0开始，对应Excel第1行 → 行号 = i+1
    if (i + 1) % 10 == 0:  # 每第10行填充
        # 从候选值中选出与当前深度差值绝对值 ≥10 的选项
        valid_vals = [v for v in candidate_test_values if abs(v - d) >= 10]
        if not valid_vals:
            # 极端情况：当前深度非常靠近边界导致无候选，则放宽到差值≥5
            valid_vals = [v for v in candidate_test_values if abs(v - d) >= 5]
        # 随机选择一个有效值
        test_val = np.random.choice(valid_vals)
        test_values.append(test_val)
    else:
        test_values.append(np.nan)  # 其余行留空

# ==================== 4. 创建 DataFrame 并导出 Excel ====================
df = pd.DataFrame(
    {
        "Depth_mm": depths_int,
        "Stability_percent": stabs_with_percent,
        "Test_Value_mm": test_values,
    }
)

output_file = "depth_stability.xlsx"
df.to_excel(output_file, index=False, sheet_name="Data")

print(f"已生成 Excel 文件：{output_file}")
print(f"共 {n_points} 行数据。")
print(f"深度范围：{depths_int.min()} ~ {depths_int.max()} mm")
non_nan = df["Test_Value_mm"].notna().sum()
print(f"测试值已填充行数：{non_nan} (每10行一个，预期 {n_points//10})")
print("测试值示例（前20行中非空的行）：")
print(df[df["Test_Value_mm"].notna()].head(10).to_string())
print("\n稳定性统计（基于数值）：")
print(f"  最小值 = {stabs_rounded.min():.1f}%")
print(f"  平均值 = {stabs_rounded.mean():.1f}%")
print(f"  低于85%的点数 = {(stabs_rounded < 85).sum()} 个")
