#include <stdio.h>

typedef struct
{
    int id;
    int distance;
} Bike;

void sort(Bike *bikes, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (bikes[j].distance > bikes[j + 1].distance)
            {
                Bike temp = bikes[j];
                bikes[j] = bikes[j + 1];
                bikes[j + 1] = temp;
            }
        }
    }
}
int main()
{

    Bike bikes[] = {
        {0, 48}, {1, 34}, {2, 100}, {3, 62}, {4, 75}, {5, 28}, {6, 69}, {7, 54}, {8, 15}, {9, 40}};
    int n = sizeof(bikes) / sizeof(bikes[0]);

    sort(bikes, n);
    printf("排序后的单车编号和距离：\n");
    for (int i = 0; i < n; i++)
    {
        printf("单车编号: %d, 距离: %d米\n", bikes[i].id, bikes[i].distance);
    }
    return 0;
}