#include <stdio.h>
#include <string.h>

// create struct with person1 variable
struct Person
{
    char name[50];
    int citNo;
    float salary;
} person1;

struct Person createPerson(){
    struct Person person2;
    printf("Enter the persons first name: ");
    scanf("%[^\n]%*c", person2.name);
    printf("Enter the persons citizenship number: ");
    scanf("%d", &person2.citNo);
    printf("Enter the persons salary: ");
    scanf("%f", &person2.salary);
    return person2;
}

int main(int argc, char *argv[])
{
    // // assign value to name of person1
    // strcpy(person1.name, "George Orwell");
    // // assign values to other person1 variables
    // person1.citNo = 1984;
    // person1.salary = 2500;

    // // print struct variables
    // printf("\nName: %s\n", person1.name);
    // printf("\nCitizenship No.: %d\n", person1.citNo);
    // printf("\nSalary: %.2f\n", person1.salary);
    // printf("\n\n");

    struct Person person2 = createPerson();
	printf("\nNew Person Information Output\n");
	printf("Name: %s\n", person2.name);
	printf("Citizenship No.: %d\n", person2.citNo);
	printf("Salary: %.2f\n", person2.salary);
	printf("\n"); 

    return 0;
}
