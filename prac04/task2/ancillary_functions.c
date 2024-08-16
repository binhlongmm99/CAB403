#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/**
 * Function to generate n random numbers between a lower and upper range
 * \param lowerRange - lowest value of random number
 * \param upperRange - largest value of random number
 * \param count - number of random numbers to generate
 */
int *genRandomIntegerNumbers(int lowerRange, int upperRange, int count)
{
  srand(time(NULL));
  int *arrayValues = malloc(sizeof(int) * count);
  if (arrayValues != NULL)
  {
    int i;
    for (i = 0; i < count; i++)
    {
      int num = (rand() % (upperRange - lowerRange + 1)) + lowerRange;
      arrayValues[i] = num;
    }
  }
  else
  {
    fprintf(stderr, "\nError allocating dynamic memory for random numbers\n");
    exit(EXIT_FAILURE);
  }
  return arrayValues;
}

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

/**
 * Comparison functions for qsort
 * compareA with sort values into non-descending order
 * compareB will sort values into non-ascending order
 */
int compareA(const void *val1, const void *val2)
{
  return (*(int *)val1 - *(int *)(val2));
}

int compareB(const void *val1, const void *val2)
{
  return (*(int *)val2 - *(int *)(val1));
}

/**
 * Print out an array of numbers
 * \param arrayValues - the array of values to print
 * \param length - length of array
 */
void printArray(const char *narr, int *arr, int length)
{
  printf("\nValues in the array\n%s ", narr);
  for (int i = 0; i < length; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

/**
 * Function to check that the name provided for shared memory object has a leading '/'
 * \param name - name provided for shared memory object
 * \returns 1 if invalid else 0
 */
int checkShMemName(char *name)
{
  if ((name[0] != '/') || (strlen(name) == 1))
  {
    return 1;
  }
  return 0;
}