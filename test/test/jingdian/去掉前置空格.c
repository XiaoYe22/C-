#include <stdio.h>
void removekb(char *str);
int main()
{
    char str[] = "   ab c   d rfr";
    printf("before remove: %s\n", str);
    removekb(str);
    printf("after remove: %s\n", str);
    return 0;
}
void removekb(char *str)
{
    if (str == NULL)
    {
        return;
    }
    char *p = str;
    while (*p == ' ')
    {
        p++;
    }
    while (*p)
    {
        *str++ = *p++;
    }
    *str = '\0';
}