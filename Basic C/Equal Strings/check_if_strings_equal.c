/**
 * Check if two strings are equal
 */

#include <stdio.h>
#include <string.h>

int main()
{
    char str1[100], str2[100];
    int flag = 0;
    printf("Enter first string: ");
    gets(str1);
    printf("Enter second string: ");
    gets(str2);
    for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
        if (str1[i] != str2[i])
        {
            flag = 1;
            break;
        }
    if (flag == 0)
        printf("Strings are equal.");
    else
        printf("Strings are not equal.");
    return 0;
}