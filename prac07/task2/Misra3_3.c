void func2(void *argument);

int main(void){
    int x;
    int *ptr = &x;
    func2(ptr);

}

void func2(void *argument)
{   
    int *ptr = argument;
    int i;
    int a[] = {1, 2, 3};             // predefine an array with three elements of type integer
    int n = sizeof(a) / sizeof(int); // variable n is assigned with the number of elements of array a, which is 3.
    for (i = 0; i < n; i++)
    { // count from the first index of an array, 0, up to n, which is now 3.
        argument = (void *)a[i];
    }
}

// array out of bound.  Change “i<=n”  to “i<n”