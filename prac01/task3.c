
#include <stdio.h>

int main()
{
    /* Declares an integer variable to hold the number read in */
    int num;
    /* Declares an integer variable to hold the sum */
    int sum;
    /* Initialise the sum */
    sum = 0;
    do
    {
        printf("Sum so far: %d\n", sum);
        printf("Enter number: ");
        /* Read in an integer from the user */
        scanf("%d", &num);
        /* Add num to sum only if positive*/
        if (num > 0)
        {
            sum = sum + num;
        }
    } while (num >= 0);
    printf("FINAL TOTAL: %d\n", sum);
    return 0;
}
