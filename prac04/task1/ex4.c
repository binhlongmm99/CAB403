#include <stdio.h>

int main(void)
{

    struct student
    {
        char id[15];
        char firstname[64];
        char lastname[64];
        float points;
    };

    struct student studentDetails;
    struct student *studentPointer = NULL;
    studentPointer = &studentDetails;
    // Enter Information
    printf("Enter ID: ");
    scanf("%s", studentPointer->id);
    printf("Enter first name: ");
    scanf("%s", studentPointer->firstname);
    printf("Enter last name: ");
    scanf("%s", studentPointer->lastname);
    printf("Enter Points: ");
    scanf("%f", &studentPointer->points);

    // display result by studentDetails struct
    printf("\nResult represented by studentDetails struct\n");
    printf("ID: %s\n", studentDetails.id);
    printf("First Name: %s\n", studentDetails.firstname);
    printf("Last Name: %s\n", studentDetails.lastname);
    printf("Points: %0.2f\n", studentDetails.points);

    // display result via studentPointer variable
    printf("\nResult represented by studentPointer\n");
    printf("ID: %s\n", studentPointer->id);
    printf("First Name: %s\n", studentPointer->firstname);
    printf("Last Name: %s\n", studentPointer->lastname);
    printf("Points: %0.2f\n", studentPointer->points);
    
    return 0;
}