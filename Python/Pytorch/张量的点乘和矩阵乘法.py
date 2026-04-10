import torch
import numpy as np

def test_dot_product():
    # 创建两个一维张量
    a = torch.tensor([1, 2, 3])
    b = torch.tensor([4, 5, 6])
    
    # 计算点乘
    dot_product = torch.dot(a, b)
    mul_result = a * b
    print(f"点乘结果: {dot_product}")
    print(f"逐元素乘积结果: {mul_result}")

def test_matrix_multiplication():
    # 创建两个二维张量
    A = torch.tensor([[1, 2], [3, 4]])
    B = torch.tensor([[5, 6], [7, 8]])
    
    # 计算矩阵乘法
    C = torch.mm(A, B)
    D = A @ B  # 另一种矩阵乘法的写法
    print(f"矩阵乘法结果:\n{C}")
    print(f"矩阵乘法结果（使用@运算符）:\n{D}")

if __name__ == "__main__":
    test_dot_product()
    test_matrix_multiplication()