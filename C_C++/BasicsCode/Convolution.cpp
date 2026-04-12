#include <iostream>
#include <vector>

using namespace std;

// 定义链表节点结构
struct ListNode
{
    vector<vector<int>> matrix; // 存储二维矩阵
    ListNode *next;             // 指向下一个节点
    ListNode(vector<vector<int>> mat) : matrix(mat), next(nullptr) {}
};

// 卷积加减函数
ListNode *convolutionAddSubtract(ListNode *list1, ListNode *list2, bool add)
{
    ListNode *resultHead = nullptr;
    ListNode *resultTail = nullptr;

    while (list1 != nullptr || list2 != nullptr)
    {
        vector<vector<int>> resultMatrix;

        if (list1 != nullptr)
        {
            resultMatrix = list1->matrix;
            list1 = list1->next;
        }
        else
        {
            resultMatrix = vector<vector<int>>(1, vector<int>(1, 0)); // 如果list1为空，初始化为0矩阵
        }

        if (list2 != nullptr)
        {
            if (add)
            {
                // 卷积加法
                for (size_t i = 0; i < resultMatrix.size(); ++i)
                {
                    for (size_t j = 0; j < resultMatrix[i].size(); ++j)
                    {
                        resultMatrix[i][j] += list2->matrix[i][j];
                    }
                }
            }
            else
            {
                // 卷积减法
                for (size_t i = 0; i < resultMatrix.size(); ++i)
                {
                    for (size_t j = 0; j < resultMatrix[i].size(); ++j)
                    {
                        resultMatrix[i][j] -= list2->matrix[i][j];
                    }
                }
            }
            list2 = list2->next;
        }

        // 创建新节点并添加到结果链表
        ListNode *newNode = new ListNode(resultMatrix);
        if (resultHead == nullptr)
        {
            resultHead = newNode;
            resultTail = newNode;
        }
        else
        {
            resultTail->next = newNode;
            resultTail = newNode;
        }
    }

    return resultHead;
}

int main()
{
    // 示例代码可以在这里创建链表并调用函数
    return 0;
}