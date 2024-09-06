// #include <stdio.h>

// int main()
// {
//     int m, error;
//     printf("Please specify the board height: \n");
//     scanf("%d", &m);
//     printf("The board height is %d\n", m);
// }


// -----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int m;
    int error;
    printf("Please specify the board height: \n");
    if (scanf("%d", &m) != 0){
        printf("The board height is %d\n", m);
    } else {
        return EXIT_FAILURE;
    }
    return 0;
}

// Rule 8.2 : Declarations : Explicitly specify void when a function accepts no argumentsLinks to an external site.
// Rule 12.3 : The comma operator should not be used.
// D.4.14 The validity of values received from external sources shall be checked