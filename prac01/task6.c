
#include <stdio.h>
#define PI 3.1416

double calculateVolume(double rad, double height);

int main(void)
{
    double radius, height;
    printf("\nEnter the radius of the cylinder: ");
    scanf("%lf", &radius);
    printf("\nEnter the height of the cylinder: ");
    scanf("%lf", &height);
    double volume = calculateVolume(radius, height);
    printf("\nThe volume of the cylinder is %lf.\n", volume);
    return 0;
}

double calculateVolume(double rad, double height)
{
    return PI * rad * rad * height;
}
