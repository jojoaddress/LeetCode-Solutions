import torch
import torch.nn as nn


def test01():
    # 1.创建样本的真实值
    y_true = torch.tensor([[1, 0, 0], [0, 1, 0], [0, 0, 1]], dtype=torch.float32)
    # 2.创建样本的预测值
    y_pred = torch.tensor(
        [[0.8, 0.1, 0.1], [0.2, 0.7, 0.1], [0.1, 0.2, 0.7]],
        requires_grad=True,
        dtype=torch.float32,
    )
    # 3.创建交叉熵损失函数
    criterion = nn.CrossEntropyLoss()
    
    # 4.计算损失值
    loss = criterion(y_pred, torch.argmax(y_true, dim=1))
    print("交叉熵损失值:", loss.item())
