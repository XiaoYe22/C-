#include <stdio.h>
// 定义单车信息结构体
typedef struct
{
    int id;       // 单车编号
    int distance; // 单车距离
} Bike;

// 冒泡排序函数，按照距离由近到远排序
void sortBikes(Bike bikes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (bikes[j].distance > bikes[j + 1].distance)
            {
                // 交换两个单车信息
                Bike temp = bikes[j];
                bikes[j] = bikes[j + 1];
                bikes[j + 1] = temp;
            }
        }
    }
}
int main()
{
    // 初始化单车数据
    Bike bikes[] = {
        {0, 48}, {1, 34}, {2, 100}, {3, 62}, {4, 75}, {5, 28}, {6, 69}, {7, 54}, {8, 15}, {9, 40}};
    int n = sizeof(bikes) / sizeof(bikes[0]); // 计算单车数量

    // 对单车数据进行排序
    sortBikes(bikes, n);

    // 输出排序后的单车编号和距离
    printf("排序后的单车编号和距离：\n");
    for (int i = 0; i < n; i++)
    {
        printf("单车编号: %d, 距离: %d米\n", bikes[i].id, bikes[i].distance);
    }
    return 0;
}