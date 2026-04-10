import torch
import numpy as np

def test01():
    # 创建一个随机张量，形状为(2, 3)，元素值在0到1之间
    t1 = torch.tensor([[0.1, 0.2, 0.3], [0.4, 0.5, 0.6]])
    print(f"t1:{t1}, dtype:{t1.dtype},type:{type(t1)}")

    # 将t1转换为numpy数组
    t2  = t1.numpy()
    print(f"t2:{t2}, dtype:{t2.dtype},type:{type(t2)}")

def test02():
    # 创建一个numpy数组
    n1 = np.array([[1, 2, 3], [4, 5, 6]])
    print(f"n1:{n1}, dtype:{n1.dtype},type:{type(n1)}")

    # 将n1转换为torch张量
    t1 = torch.from_numpy(n1)
    print(f"t1:{t1}, dtype:{t1.dtype},type:{type(t1)}")

    # 将n1转换为torch张量，并指定数据类型为float32,不共享内存
    t2 = torch.tensor(n1, dtype=torch.float32)
    print(f"t2:{t2}, dtype:{t2.dtype},type:{type(t2)}")

if __name__ == "__main__":
    test01()
    test02()