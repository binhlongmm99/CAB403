#include <stdint.h>

//#include
extern void panic (void);
extern void func1 (uint32_t a);
extern uint32_t failure;

void func1 (uint32_t  a) {
    /* default path C:\Test\ */
    uint32_t path = 0; 
    if (failure)
    {
        panic();
    }
}

// Use /*   */ style comment 
