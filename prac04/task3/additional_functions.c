#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/**
 * Function to check char array contains only integers represented by a char
 * \param value[] - array of chars
 * \return 0 true else 1 false
 */
int isNumber(char value[])
{
    int i;
    for (i = 0; value[i] != '\0'; i++)
    {
        if (isdigit(value[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}