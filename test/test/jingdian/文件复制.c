#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *fp1, *fp2;
    char ch;
    fp1 = fopen("abc.txt", "r");
    fp2 = fopen("out.txt", "w");
    if (fp1 == 0)
    {
        printf("文件打开失败");
        exit(0);
    }
    ch = fgetc(fp1);
    while (!feof(fp1))
    {
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
        {
            fputc(ch, fp2);
        }
        else
        {
            putchar(ch);
        }
        ch = fgetc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}