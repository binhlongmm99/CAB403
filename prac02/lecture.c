#include <stdio.h>
#include <stdlib.h>

#define arrayLength(array) (sizeof((array)) / sizeof((array)[0]))

void * f() {
      void *p = malloc(100); // allocate 100 bytes 
      p = malloc(200);      // allocate 200 bytes

      return p;
}


int main()
{

    // ---------------------------------------------------------------------------------------------------------------
    // macro
    int arrayOne[] = {15, 22, 18, 34, 1, 10};                                                        // 6 elements
    float arrayTwo[] = {12.45, 18.34, 20.55, 13.12, 88.62, 100.12, 64.23, 99.99, 121.23};            // 9 elements
    char arrayThree[] = {'m', 'a', 'c', 'r', 'o', 'd', 'e', 'f', 'i', 'n', 'i', 't', 'i', 'o', 'n'}; // 15 elements
    double arrayFour[] = {1.2, 1.3, 2.5};

    int lengthArrayOne = arrayLength(arrayOne);
    int lengthArrayTwo = arrayLength(arrayTwo);
    int lengthArrayThree = arrayLength(arrayThree);
    int lengthArrayFour = arrayLength(arrayFour);

    printf("\n\nThe length of arrayOne = %d\nThe length of arrayTwo = %d\nThe length of arrayThree = %d\n\n",
           lengthArrayOne, lengthArrayTwo, lengthArrayThree);
    printf("Length of arrayFour = %d\n", lengthArrayFour);


    // ---------------------------------------------------------------------------------------------------------------
    // memory leak
    f();


    // ---------------------------------------------------------------------------------------------------------------
    // string in C
    char myString[14] = "cab403Program";                                                          // String literal
    char charArray[14] = {'c', 'a', 'b', '4', '0', '3', 'P', 'r', 'o', 'g', 'r', 'a', 'm', '\0'}; // char array
    char *charPtr = "cab403Program";
    printf("\nChar array value is %s\n", charArray);
    printf("\nString literal value is %s\n", myString);
    printf("\nChar pointer value is %s\n\n", charPtr);

    char str[100];
    // using the scanset
    printf("Enter a string: ");
    scanf("%[^\n]%*c", str);
    printf("%s\n", str);
    // using the fgets

    fgets(str, sizeof(str), stdin);

    // ---------------------------------------------------------------------------------------------------------------

    return 0;
}