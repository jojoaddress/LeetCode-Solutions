import torch
import numpy as np


def test01():
    torch.manual_seed(4)  # 设置随机种子以获得可重复的结果

    t1 = torch.randint(0, 10, (5, 5))
    print(f"原始张量:\n{t1}")
    print(t1[:, 2])
    print(t1[1, :])

    print(t1[[1, 3, 2], [0, 2, 2]])

    # 选择第0行和第1行的第0列和第1列的元素
    print(t1[[[0], [1]], [0, 1]])

    # 所有奇数行和偶数列的元素
    print(t1[1::2, ::2])


def test02():
    torch.manual_seed(4)  # 设置随机种子以获得可重复的结果

    t1 = torch.randint(0, 10, [2, 2, 3])
    print(f"原始张量:\n{t1}")

    print(t1[0, :, :])
    print(t1[:, 0, :])
    print(t1[:, :, 0])


if __name__ == "__main__":
    # test01()
    test02()
