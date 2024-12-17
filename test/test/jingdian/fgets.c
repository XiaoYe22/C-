#include <stdio.h>
int main()
{
    FILE f1 = *fopen("out.txt", "r");
    char str[20];
    printf("Enter a string: ");
    fgets(str, 20, stdin);
    printf("You entered: %s", str);
}