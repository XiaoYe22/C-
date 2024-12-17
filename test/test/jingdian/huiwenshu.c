
#include <stdio.h>
#include <string.h>

int sumhw(char **p, int n);
char jughw(char *str);

void main(int argc, char *argv[])
{
    int s;
    if (argc < 2)
        printf("请输入有效参数");
    else
    {
        s = sumhw(argv + 1, argc - 1);
        printf("共有%d个参数\n", argc);
        printf("共有%d个回文串\n", s);
    }
}
int sumhw(char **p, int n)
{
    char flag;
    int i, j, k, sum = 0;
    for (i = 0; i < n; i++)
    {
        flag = jughw(p[i]);
        if (flag == 'Y')
            sum++;
    }
    return sum;
}

char jughw(char *str)
{
    char *p1, *p2;
    int n;
    n = strlen(str);
    p1 = str;
    p2 = str + n - 1;
    while (p1 < p2)
    {
        if (*p1 != *p2)
            break;
        else
        {
            p1++;
            p2--;
        }
    }
    if (p1 < p2)
        return 'N';
    else
        return 'Y';
}