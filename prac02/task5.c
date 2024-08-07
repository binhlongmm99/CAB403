#include <stdio.h>

int main(void)
{
    char *cityPtr[4] = {"Toowong", "Chermside", "Taringa", "Indooroopilly"};
    // temporary variable
    int c;
    // print cities
    for (int i = 0; i < 4; i++)
    {
        c = 0;
        while (*(cityPtr[i] + c) != '\0')
        {
            printf("%c", *(cityPtr[i] + c));
            c++;
        }
        printf("\n");
    }
    return 0;
}
