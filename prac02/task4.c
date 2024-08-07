
#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void enterValuesIntoArr(int *ptr, int length);
void printOutArray(int *ptr, int length);
int askUserToIncreaseArraySize(int *ptr, int length);
void enterValuesIntoExistingArray(int *ptr, int totalSize, int start);

int main(int argc, char *argv[])
{
    int numElements = 0;
    int *arrOnePtr;

    // ask user to determine the array size
    printf("\nEnter the number of elements in an array: ");
    scanf("%d", &numElements);

    // allocate sufficient memory and check memory allocation is successful
    arrOnePtr = malloc(numElements * sizeof(int));
    if (arrOnePtr == NULL)
    {
        printf("\nMemory allocation failed\n");
        return EXIT_FAILURE;
    }
    else
    {
        printf("Memory successfully allocated (%ld bytes)\n", numElements *
                                                                  sizeof(int));
    }
    enterValuesIntoArr(arrOnePtr, numElements);
    printOutArray(arrOnePtr, numElements);
    int newSize = askUserToIncreaseArraySize(arrOnePtr, numElements);
    enterValuesIntoExistingArray(arrOnePtr, newSize, numElements);
    printOutArray(arrOnePtr, newSize);

    return 0;
}

void enterValuesIntoExistingArray(int *ptr, int totalSize, int start)
{
    for (int i = start; i < totalSize; i++)
    {
        printf("Enter new value to append to array: ");
        scanf("%d", &ptr[i]);
    }
}
int askUserToIncreaseArraySize(int *ptr, int length)
{
    int additionalElements = 0;
    printf("The array currently contains %d integers.\n", length);
    printf("Enter the number of elements to be added: ");
    scanf("%d", &additionalElements);

    // reallocate memory for the additional elements
    ptr = realloc(ptr, (length + additionalElements) * sizeof(int));
    if (ptr == NULL)
    {
        printf("\nMemory allocation failed\n");
        return EXIT_FAILURE;
    }
    else
    {
        printf("\nMemory successfully allocated\n");
        printf("Array now has sufficient memory for %d integers\n", (length + additionalElements));
    }

    return length + additionalElements;
}

void enterValuesIntoArr(int *ptr, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("Enter a value to store in array: ");
        scanf("%d", &ptr[i]);
    }
}

void printOutArray(int *ptr, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("array[%d] = %d || ", i, ptr[i]);
    }
    printf("\n\n");
}
