import torch


def test01():
    # W新 = W旧 - 学习率 * 梯度

    # 1.定义变量：记录W旧
    W = torch.tensor(10, requires_grad=True, dtype=torch.float32)
    # 2.定义损失函数：loss = (W - 5) ** 2
    loss = (W - 5) ** 2
    # 3.反向传播：计算梯度
    loss.backward()#结果 W.grad = 2 * (W - 5) = 10
    # 4.更新权重：W新 = W旧 - 学习率 * 梯度
    learning_rate = 0.1
    W.data = W.data - learning_rate * W.grad.data
    # 5.打印
    print(W.data) 

def test02():
    W = torch.tensor(10, requires_grad=True, dtype=torch.float32)
    #迭代100次，求最优解
    for i in range(100):
        loss = W ** 2 + 20
        loss.backward()
        learning_rate = 0.1
        W.data = W.data - learning_rate * W.grad.data
        print(f"第{i+1}次迭代，W={W.data:.4f},grad={W.grad.data:.4f}, loss={loss.data:.4f}")
        W.grad.data.zero_()#清空梯度

def test03():
    #1.定义张量
    W = torch.tensor([10,20], requires_grad=True, dtype=torch.float32)
    print(f"初始W：{W.data}")
    #2.转换为numpy数组
    W_np = W.detach().numpy()
    print(f"转换为numpy数组：{W_np}")

    # 推荐：始终使用 W.detach().cpu().numpy()（若需要 CPU 数组）。
    # 避免：使用 W.data.numpy()，因为它是一种“隐式”且可能产生副作用的旧式用法。

if __name__ == "__main__":
    #test01()
    #test02()
    test03()