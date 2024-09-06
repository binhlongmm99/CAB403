/*
 * R_21_15.c
 * Release: 2022-09-02
 * Example from MISRA C:2012 AMD1
 * Copyright: Queensland University of Technology
 * Reference:  https://gitlab.com/MISRA/MISRA-C/MISRA-C-2012/Example-Suite)
 */

/* memcpy() copies "numBytes" bytes from address "from" to address "to"
 * void * memcpy(void *to, const void *from, size_t numBytes);
 * note: memcpy() doesn’t check for overflow or \0
 */

/*
 * R.21.15
 * The pointer arguments to the Standard Library functions memcpy,
 * memmove and memcmp shall be pointers to compatible types
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

static void f_15(uint8_t s1[8], uint16_t s2[8])
{
  (void)memcpy(s1, s2, 8); /* Non-compliant */

  // display the content of s1
  for (int loop = 0; loop < 8; loop++)
    printf("%d \t ", s1[loop]);
  printf(" \n");
}

int main(void)
{
  uint8_t loc_s1[8];
  uint16_t loc_s2[8] = {1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U};
  f_15(loc_s1, loc_s2);
}

/* end of R_21_15.c */
