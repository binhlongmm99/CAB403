#include <stdio.h>
#include <limits.h>

int main(void)
{
    char *char_ptr;
    int *int_ptr;
    long *long_ptr;
    short *short_ptr;
    float *float_ptr;
    double *double_ptr;
    char *far_char_ptr;
    struct test_tag
    {
        char a;
        int b;
    } test_struct;

    printf("\nThe minimum value of a signed integer is %d", INT_MIN);
    printf("\nThe maximum value for a signed integer is %d", INT_MAX);

    printf("\n Type Size ");
    printf("\n==========================");
    printf("\n character \t\t%zu ", sizeof(char));
    printf("\n integer \t\t%zu ", sizeof(int));
    printf("\n short \t\t\t%zu ", sizeof(short));
    printf("\n long \t\t\t%zu ", sizeof(long));
    printf("\n float \t\t\t%zu ", sizeof(float));
    printf("\n double \t\t%zu ", sizeof(double));
    printf("\n char pointer \t\t%zu ", sizeof(char_ptr));
    printf("\n int pointer \t\t%zu ", sizeof(int_ptr));
    printf("\n short pointer \t\t%zu ", sizeof(short_ptr));
    printf("\n long pointer \t\t%zu ", sizeof(long_ptr));
    printf("\n float pointer \t\t%zu ", sizeof(float_ptr));
    printf("\n double pointer \t%zu ", sizeof(double_ptr));
    printf("\n far char pointer \t%zu ", sizeof(far_char_ptr));
    printf("\n test_structure \t%zu ", sizeof(test_struct));
    printf("\n==========================\n\n");
    return 0;
}
