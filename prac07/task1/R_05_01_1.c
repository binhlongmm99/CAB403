/*
 * R_5_1_1.c
 * Reference:  https://gitlab.com/MISRA/MISRA-C/MISRA-C-2012/Example-Suite
 */

/*
 * R.5.1
 *
 * External identifiers shall be distinct
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "R_05_01.h"

/* int32_t: alias for integer type that is exactly  32 bits
        1234567890123456789012345678901********* Characters */
int32_t engine_exhaust_gas_temperature_raw;
int32_t engine_exhaust_gas_temperature_scaled; /* Non-compliant */

/*      1234567890123456789012345678901********* Characters */
int32_t engine_exhaust_gas_temp_raw;
int32_t engine_exhaust_gas_temp_scaled; /* Compliant */

extern int32_t abc;
int32_t abc = 0;

static void R_5_1_1(void)
{
    engine_exhaust_gas_temperature_raw = 100;
    engine_exhaust_gas_temperature_scaled = 1000;
    engine_exhaust_gas_temp_raw = 200;
    engine_exhaust_gas_temp_scaled = 2000;
    abc = 10;
}

int main(void)
{
    R_5_1_1();

    printf("%d \n", engine_exhaust_gas_temperature_raw);
    printf("%d \n", engine_exhaust_gas_temperature_scaled);
    printf("%d \n", engine_exhaust_gas_temp_raw);
    printf("%d \n", engine_exhaust_gas_temp_scaled);
    printf("%d \n", abc);

    R_5_1_2();
}
/* end of R_05_01_1.c */
