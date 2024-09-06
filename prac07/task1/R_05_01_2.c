/*
 * R_5_1_2.c
 * Reference:  https://gitlab.com/MISRA/MISRA-C/MISRA-C-2012/Example-Suite)
 */

/*
 * R.5.1
 *
 * External identifiers shall be distinct
 */

#include <stdio.h>
#include <stdint.h>
#include "R_05_01.h"

int32_t ABC;
int32_t ABC = 0; /* Non-compliant  */

static void R_5_1_2_1(void)
{
    ABC = 20;
}

void R_5_1_2(void)
{
    R_5_1_2_1();

    printf("%d \n", engine_exhaust_gas_temperature_raw);
    printf("%d \n", engine_exhaust_gas_temperature_scaled);
    printf("%d \n", engine_exhaust_gas_temp_raw);
    printf("%d \n", engine_exhaust_gas_temp_scaled);
    printf("%d \n", ABC);
}

/* end of R_05_01_2.c */
