// 用指针和数组两种方法实现如下功能：将一个字符串按逆序存放。
// （1）主函数中完成输入和输出字符串。
// （2）逆序存放功能用子函数完成。
#include <stdio.h>
#include <string.h>

// 数组版本
// void reverseStringArray(char str[]);
void reverseStringPointer(char *str);
int main()
{
    char str[100];
    printf("请输入一个字符串: ");
    gets(str);
    reverseStringPointer(str);
    printf("逆序后的字符串：\n");
    puts(str);
    return 0;
    // scanf("%s", str);
    // reverseStringArray(str);
    // printf("逆序后的字符串: %s\n", str);
}

// 数组版本
/* void reverseStringArray(char str[])
{
    int start;
    int end = strlen(str) - 1;
    char temp;
    // while版本
    while (start < end)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    for (start = 0; start < end; start++, end--)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
    }
} */
void reverseStringPointer(char *str)
{
    char *start = str;
    int n = strlen(str);
    char *end = str + n - 1;
    char temp;
    for (start; start < end; start++, end--)
    {
        temp = *start;
        *start = *end;
        *end = temp;
    }
}