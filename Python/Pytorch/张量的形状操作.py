import torch
import numpy as np


# reshape、view、squeeze、unsqueeze、transpose、permute、contiguous、 is_contiguous等函数的使用
def test01():
    torch.manual_seed(4)  # 设置随机种子以获得可重复的结果
    t1 = torch.randint(0, 10, (2, 3))
    print(f"原始张量:\n{t1}")

    # reshape函数
    t2 = t1.reshape((3, 2))
    print(f"reshape后的张量:\n{t2}")

    # view函数
    # 只能修改连续存储的张量的形状，如果张量不是连续的，则需要先调用contiguous函数
    t3 = t1.view((3, 2))
    print(f"view后的张量:\n{t3}")

    # squeeze函数
    t4 = torch.randint(0, 10, (1, 2, 3, 1))
    print(f"原始张量:\n{t4}, shape:{t4.shape}")
    t5 = t4.squeeze()
    print(f"squeeze后的张量:\n{t5}, shape:{t5.shape}")

    # unsqueeze函数
    t6 = t5.unsqueeze(0)
    print(f"unsqueeze后的张量:\n{t6},shape:{t6.shape}")

    # transpose函数
    t7 = t1.transpose(0, 1)
    print(f"transpose后的张量:\n{t7}")

    # permute函数
    t8 = t1.permute(1, 0)
    print(f"permute后的张量:\n{t8}")

    # contiguous函数
    t9 = t1.transpose(0, 1).contiguous()
    print(f"contiguous后的张量:\n{t9}")
    print(f"t1是否连续: {t1.is_contiguous()}")

if __name__ == "__main__":
    test01()