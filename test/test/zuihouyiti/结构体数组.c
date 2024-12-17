#include <stdio.h>
#include <string.h>
struct Person
{
    char name[20];
    int count;
} leader[3] = {"zhangsan", 10, "lisi", 11, "wangwu", 12};
int main()
{
    int i;
    for (i = 0; i < 3; i++)
    {
        printf("%s %d\n", leader[i].name, leader[i].count);
    }
    return 0;
}
