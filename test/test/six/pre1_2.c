/*
一个整型数组有 10 个元素，编写程序删除所有值为 n 的元素。
（1）主函数完成 n 的输入，数组元素输入以及删除后数组元素的输出。
（2）删除功能用子函数完成。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

int delete(int a[], int n);
int main()
{
    int a[N];
    int i, n, j;
    printf("请输入10个整数：\n");
    for (i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("请输入想删除的整数:");
    scanf("%d", &n);
    j = delete (a, n);
    printf("删除后的数组为:\n");
    for (i = 0; i < j; i++)
    {
        printf("%d ", a[i]);
    }
}

int delete(int a[], int n)
{
    int i, j = 0;
    for (i = 0; i < N; i++)
    {
        if (a[i] != n)
        {
            a[j] = a[i];
            j++;
        }
    }
    return j;
}
