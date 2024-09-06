/*
 * R.21.17.c
 * Release: 2022-09-02
 * Example from MISRA C:2012 AMD1
 * Copyright: Queensland University of Technology
 * Reference:  https://gitlab.com/MISRA/MISRA-C/MISRA-C-2012/Example-Suite)
 */

/*
 * R.21.17
 * Use of the string handling functions from <string.h> shall not result in
 * accesses beyond the bounds of the objects referenced by their pointer parameters
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

static void f_17(const char *str)
{
  char string[] = "Short";

  printf("%s \n", string); /* we directly use stdio here. you should define your own IO. */

  /* Non-compliant use of strcpy as it
   *  results in writes beyond the end of 'string'
   * Also breaks R.21.18
   */

  /* ( void ) strcpy ( string, "Too long to fit " );
   printf( "%s",string );
   */

  /*
   * Compliant use of strcpy as 'string' is only mocified if 'str' will fit.
   */

  if (strlen(str) < (sizeof(string) - 1U)) /* Compliant */
  {
    (void)strcpy(string, str);
  }

  printf("%s \n", string);
}

static void g_17(void)
{
  size_t sz;
  size_t sz1;
  char text[5] = "Token"; /* Non-compliant */
  char text1[10] = {'T', 'o', 'k', 'e', 'n', '\0'};
  /*
   * The following is non-compliant as it results in
   * Reads beyond the end of 'text' as there is no null terminator.
   * NOTE: the strlen() function doesn't count the null character \0
   * while calculating the length.
   */
  sz = strlen(text); /* Non-compliant */
  sz1 = strlen(text1);

  if (sz > 1U)
  {
    /* use “%zu” to print the variables of size_t length. */
    printf("%zu \n", sz);
  }

  if (sz1 > 1U)
  {
    /* use “%zu” to print the variables of size_t length. */
    printf("%zu \n", sz1);
  }
}

int main(void)
{
  f_17("Tiny");
  f_17("Small");
  g_17();
}

/* end of R_21_17.c */
