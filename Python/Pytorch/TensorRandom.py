import torch
import numpy as np


def test01():
    # 创建一个随机张量，形状为(2, 3)，元素值在0到1之间
    t1 = torch.rand((2, 3))
    print(f"t1:{t1}")

    # 创建一个随机整数张量，形状为(2, 3)，元素值在0到10之间
    t2 = torch.randint(0, 10, (2, 3))
    print(f"t2:{t2}")

    # 创建一个随机正态分布张量，形状为(2, 3)，均值为0，标准差为1
    t3 = torch.randn((2, 3))
    print(f"t3:{t3}")

    # 获取当前随机数生成器的种子
    t4 = torch.initial_seed()
    print(f"t4:{t4}")

    t5 = torch.manual_seed(2)  # 设置随机数生成器的种子为2
    print(f"t5:{t5}")

def test02():
    # 创建一个从0到9的等差数列张量，步长为3
    t1 = torch.arange(0, 10, 3)
    print(f"t1:{t1}")

    # 创建一个从0到1的等差数列张量，包含5个元素
    t2 = torch.linspace(0, 1, steps=5)
    print(f"t2:{t2}")



if __name__ == "__main__":
    test01()
