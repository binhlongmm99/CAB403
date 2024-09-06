#include <stdio.h>

int Fibonacci(int);

int main()
{
   int n, i = 0, c;
   printf("Enter the number of elements:");

   scanf("%d", &n);

   printf("Fibonacci series\n");

   for (c = 1; c <= n; c++)
   {
      printf("%d\n", Fibonacci(i));
      i++;
   }

   return 0;
}

// int Fibonacci(int n)
// {
//    if (n == 0)
//       return 0;
//    else if (n == 1)
//       return 1;
//    else
//       return (Fibonacci(n - 1) + Fibonacci(n - 2));
// }

int Fibonacci(int n)
{
   int last = 1; /* Initial value is fib (1).  */
   int prev = 0; /* Initial value controls fib (2).  */
   int i;

   for (i = 1; i < n; ++i)
   /* If n is 1 or less, the loop runs zero times,  */
   /* since i < n is false the first time.  */
   {
      /* Now last is fib (i)
         and prev is fib (i - 1).  */
      /* Compute fib (i + 1).  */
      int next = prev + last;
      /* Shift the values down.  */
      prev = last;
      last = next;
      /* Now last is fib (i + 1)
         and prev is fib (i).
         But that won’t stay true for long,
         because we are about to increment i.  */
   }

   return last;
}