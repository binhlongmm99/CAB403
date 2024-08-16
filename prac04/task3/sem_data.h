#include <semaphore.h>
/**
 * Data structure for application
 * Struct contains a semaphore for process synchronisation
 * and a char array that will be populated by the child processes
 */

typedef struct sm_data
{
    sem_t child_process_lock;
    char buffer[1024];
} data_share_t;
