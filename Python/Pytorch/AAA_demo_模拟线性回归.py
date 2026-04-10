import torch
from torch.utils.data import Dataset, DataLoader  # 数据集和数据加载器
from torch.utils.data import (
    TensorDataset,
)  # TensorDataset是一个简单的数据集类，可以将张量数据包装成一个数据集对象，方便使用DataLoader进行批量加载
from torch import nn  # 神经网络模块，包含了各种神经网络层和损失函数等
from torch import optim  # 优化器模块，包含了各种优化算法，如SGD、Adam等
from sklearn.datasets import (
    make_regression,
)  # 生成回归数据集的函数，可以生成具有指定特征数和样本数的随机回归数据集
import matplotlib.pyplot as plt  # 绘图库，用于数据可视化

plt.rcParams["font.sans-serif"] = ["SimHei"]  # 设置中文字体为SimHei，解决中文显示问题
plt.rcParams["axes.unicode_minus"] = False  # 解决负号显示问题

# numpy对象->张量Tensor->Dataset->DataLoader->模型训练


def create_dataset():
    # 1.生成数据
    x, y, coef = make_regression(
        n_samples=100, n_features=1, noise=20, coef=True, random_state=3
    )
    # 2.转换为张量
    x = torch.tensor(x, dtype=torch.float32)  # 将x转换为张量，数据类型为float32
    y = torch.tensor(y, dtype=torch.float32).unsqueeze(1)  # 将y转换为张量，数据类型为float32，并增加一个维度，使其成为列向量

    return x, y, coef

def train(x, y, coef):
    # 1.创建数据集对象
    dataset = TensorDataset(x, y)  # 将x和y包装成一个TensorDataset对象，方便使用DataLoader进行批量加载
    # 2.创建数据加载器对象
    dataloader = DataLoader(dataset, batch_size=16, shuffle=True)  # 创建一个DataLoader对象，设置批量大小为16，并启用数据洗牌
    # 3.定义模型
    model = nn.Linear(1, 1)  # 创建一个线性模型，输入特征数为1，输出特征数为1
    # 4.定义损失函数和优化器
    criterion = nn.MSELoss()  # 定义均方误差损失函数
    optimizer = optim.SGD(model.parameters(), lr=0.01)  # 定义随机梯度下降优化器，学习率为0.01
    # 5.训练模型
    epochs = 100  # 设置训练轮数为100
    loss_list = []  # 创建一个列表来存储每轮的损失值

    for epoch in range(epochs):
        total_loss = 0  # 初始化总损失为0
        total_samples = 0  # 初始化总样本数为0
        for batch_x, batch_y in dataloader:  # 遍历数据加载器，获取每个批次的输入和标签
            optimizer.zero_grad()  # 清零梯度
            outputs = model(batch_x)  # 前向传播，计算模型的输出
            loss = criterion(outputs, batch_y)  # 计算损失值
            total_loss += loss.item() # 累加当前批次的损失值，loss.item()返回一个Python数值，表示当前批次的损失值
            total_samples += 1 # 累加当前批次的样本数
            loss.backward()  # 反向传播，计算梯度
            optimizer.step()  # 更新模型参数
            optimizer.zero_grad()  # 清零梯度
        # 每轮结束后，计算平均损失并存储
        average_loss = total_loss / total_samples  # 计算平均损失
        loss_list.append(average_loss)  # 将平均损失添加到列表中
        print(f"Epoch [{epoch+1}/{epochs}], Loss: {average_loss:.4f}")  # 打印当前轮数和平均损失

    # 6.可视化损失曲线
    plt.plot(loss_list)  # 绘制损失曲线
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.title("Training Loss")
    plt.show()

    # 7.绘制预测值与真实值的散点图
    plt.scatter(x.numpy(), y.numpy(), label="真实值", color="blue")  # 绘制真实值的散点图，颜色为蓝色
    y_pred = torch.tensor(data=[v*model.weight + model.bias for v in x], dtype=torch.float32)  # 计算预测值，使用模型的权重和偏置进行线性变换
    y_true = torch.tensor(data=[v*coef for v in x], dtype=torch.float32)  # 计算真实值，使用真实系数coef进行线性变换
    plt.plot(x,y_pred, label="预测值", color="red")  # 绘制预测值的线图，颜色为红色
    plt.plot(x,y_true, label="真实值", color="green")  #
    plt.legend()  # 显示图例
    plt.grid()  # 显示网格
    plt.show()  # 显示图形



if __name__ == "__main__":
    x, y, coef = create_dataset()
    print(f"特征数据x的形状：{x.shape}, 标签数据y的形状：{y.shape}, 真实系数coef：{coef}")
    train(x, y, coef)
