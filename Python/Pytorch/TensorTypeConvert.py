import torch
import numpy as np


def test01():
    # 创建一个随机张量，形状为(2, 3)，元素值在0到1之间
    t1 = torch.rand((2, 3))
    print(f"t1:{t1}, dtype:{t1.dtype},type:{type(t1)}")

    # 将t1转换为numpy数组
    t2  = t1.numpy()
    print(f"t2:{t2}, dtype:{t2.dtype},type:{type(t2)}")

    # 将t1转换为整数类型的张量
    t3 = t1.to(torch.int32) 
    print(f"t3:{t3}, dtype:{t3.dtype},type:{type(t3)}")

    t4 = torch.tensor([1, 2, 3], dtype=torch.float32)
    print(f"t4:{t4}, dtype:{t4.dtype},type:{type(t4)}")

    t5 = t4.type(torch.int64)
    print(f"t5:{t5}, dtype:{t5.dtype},type:{type(t5)}")

if __name__ == "__main__":
    test01()
