#include <stdio.h>

#define PI 3.142
#define areaOfCircle(radius) (PI * radius * radius)

int main(int argc, char *argv[])
{
    float userInput = 0;
    for (int i = 0; i < 5; i++)
    {
        printf("\nEnter the radius of circle %d: ", i + 1);
        scanf("%f", &userInput);
        printf("The area of the circle is: %.2f\n",
               areaOfCircle(userInput));
    }
    return 0;
}
