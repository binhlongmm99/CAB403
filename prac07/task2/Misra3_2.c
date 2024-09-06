#include <stdint.h>

void f1(void)
{
   uint16_t code[10];

   code[0] = 109;
   code[1] = 100;
   code[2] = 052;
   code[3] = 071;
}

// code[ 0 ] = 109U;      /* Compliant     - decimal 109    */
// code[ 1 ] = 100U;      /* Compliant     - decimal 100    */
// code[ 2 ] = 052;      /* Non-Compliant - decimal 42     */
// code[ 3 ] = 071;      /* Non-Compliant - decimal 57     */
