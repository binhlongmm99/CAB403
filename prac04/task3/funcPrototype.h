/**
 * Function prototypes for application
 */
#include <semaphore.h>
#include <sem_data.h>

int isNumber(char value[]);
void work(int id, data_share_t *data);
int splitProcess(int childNumber, data_share_t *data);
int createSharedMemoryObject(char *name);
data_share_t *mapSHMObject(int fd);
void unMapClose(data_share_t *data, int fd);
