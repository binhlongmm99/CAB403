
#include <stdio.h>

int main(void)
{
    char myChar = 'r';
    int k = 72; /* 65 is the ASCII encoding for 'A' */

    printf("The value printed is %c\n", k);
    printf("The value printed is %d\n", k + 3);
    printf("The value printed is %c\n", k + 3);
    printf("The value printed is %c\n", myChar + 3);

    /* Get input from the user as a char */
    int newChar;
    printf("Enter a char: ");
    newChar = getchar();
    printf("\nThe char entered was %c and the equivalent int is %d\n",
           newChar, newChar);

    char anotherChar;
    printf("\nEnter another char: ");
    scanf("%c", &anotherChar);
    printf("\nThe char entered was %c and the equivalent int is %d\n", anotherChar,
           anotherChar);
    return 0;
}
