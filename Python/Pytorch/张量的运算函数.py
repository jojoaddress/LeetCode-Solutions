import torch
import numpy as np

def test01():
    #均值
    t1 = torch.tensor([1.0, 2.0, 3.0])
    mean_value = torch.mean(t1)
    print(f"均值: {mean_value}")

    #平方根
    sqrt_value = torch.sqrt(t1)
    print(f"平方根: {sqrt_value}")

    #求和
    sum_value = torch.sum(t1)
    print(f"求和: {sum_value}")

    #指数计算
    exp_value = torch.exp(t1)
    print(f"指数: {exp_value}")

    #对数计算
    log_value = torch.log(t1)
    print(f"对数: {log_value}")

    #有dim参数的函数：
    t2 = torch.tensor([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]])
    mean_value_dim0 = torch.mean(t2, dim=0)
    mean_value_dim1 = torch.mean(t2, dim=1)
    print(f"按dim=0求均值: {mean_value_dim0}")
    print(f"按dim=1求均值: {mean_value_dim1}")

if __name__ == "__main__":
    test01()