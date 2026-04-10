import torch
import numpy as np


def test01():
    # cat,stack等函数的使用
    # cat和concat函数的功能相同，都是沿着指定维度拼接张量，区别在于cat函数要求输入的张量必须具有相同的形状，而concat函数则不要求输入的张量具有相同的形状。
    # stack函数则是在指定维度上增加一个新的维度，并将输入的张量沿着这个新维度拼接起来。
    t1 = torch.randint(0, 10, (2, 2))
    t2 = torch.randint(0, 10, (2, 2))
    print(f"t1:\n{t1}")
    print(f"t2:\n{t2}")

    # 沿着第0维拼接, 除了拼接的维度外，其他维度的形状必须相同
    cat_result = torch.cat((t1, t2), dim=0)
    print(f"cat结果:\n{cat_result}")

    # 沿着第1维拼接, 要求输入的张量具有相同的形状
    stack_result = torch.stack((t1, t2), dim=2)
    print(f"stack结果:\n{stack_result}")


if __name__ == "__main__":
    test01()
