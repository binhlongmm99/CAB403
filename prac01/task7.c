#include <stdio.h>

void swapVariables(int *ptn1, int *pnt2);

int main(void) {
    int a = 45;
    int b = 22;
    int *p1 = 0;
    int *p2 = 0;

    /* & symbol tells p1 and p2 to point to the memory address where a and b is stored respectively */
    p1 = &a;    
    p2 = &b;
    /* 
    To print the value in the memory location that pointer is pointing to we need to use the dereferencing operator * 
    */
    printf("The value of p1 is %d and the memory address location is %p\n", *p1, p1);  
    printf("The value of p2 is %d and the memory address location is %p\n", *p2, p2);
    swapVariables(&a, &b);
    printf("The value of p1 is %d and the memory address location is %p\n", *p1, p1); 
    printf("The value of p2 is %d and the memory address location is %p\n", *p2, p2);
    return 0;
}

void swapVariables(int *pnt1, int *pnt2) {      
    int temp = 0;
    temp = *pnt1;
    *pnt1 = *pnt2;
    *pnt2 = temp;
} 