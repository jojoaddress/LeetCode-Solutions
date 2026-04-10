import torch
import numpy as np


def test01():
    # 创建一个标量张量
    t1 = torch.tensor(10)
    print(f"t1:{t1}")

    data = [[1, 2], [3, 4]]
    t2 = torch.tensor(data)
    print(f"t2:{t2}")

    data = np.random.randint(0, 10, size=(2, 3))
    t3 = torch.Tensor(data)
    print(f"t3:{t3}")

    # 创建一个全1的张量
    t4 = torch.ones((2, 3))
    print(f"t4:{t4}")

    # 创建一个与t3形状相同的全1张量
    t5 = torch.ones_like(t3)
    print(f"t5:{t5}")

    # 创建一个全0的张量
    t6 = torch.zeros((2, 3))
    print(f"t6:{t6}")

    # 创建一个全5的张量
    t7 = torch.full((2, 3), 255)
    print(f"t7:{t7}")
if __name__ == "__main__":
    test01()
