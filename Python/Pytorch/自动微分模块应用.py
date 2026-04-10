import torch

#1.先前向传播，计算出预测值z
#2.基于损失函数，结合预测值和真实值，来计算梯度
#3.基于梯度，来更新权重参数

def test01():
    # x@w+b=z
    x = torch.ones(2,5) #表示输入数据，2行5列，2个样本，每个样本5个特征
    y = torch.zeros(2,3) #表示标签，真实值
    w = torch.randn(5,3,requires_grad=True) #表示权重参数，5行3列，输入特征数为5，输出特征数为3，requires_grad=True表示需要计算梯度
    b = torch.randn(3,requires_grad=True) #表示偏置参数，3个输出特征对应3个偏置，requires_grad=True表示需要计算梯度
    z = torch.matmul(x,w)+b #表示预测值，z的计算方式是输入数据x与权重参数w进行矩阵乘法，然后加上偏置参数b
    print(f'x: {x}')
    print(f'y: {y}')
    print(f'w: {w}')
    print(f'b: {b}')
    print(f'z: {z}')

    # 定义损失函数
    crierion = torch.nn.MSELoss()
    loss = crierion(z,y)
    print(f'loss: {loss}')

    #自动微分
    loss.backward() #反向传播，计算梯度

    # 输出梯度
    print(f'w的梯度: {w.grad}')
    print(f'b的梯度: {b.grad}')

    


if __name__ == "__main__":
    test01()