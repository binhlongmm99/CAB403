#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("The number of command line arguments is %d\n", argc);
    printf("The name of the program is %s\n", argv[0]);
    for (int i = 0; i < argc; i++)
    {
        printf("Command line argument %d is %s\n", i + 1, argv[i]);
    }

    return 0;
}
