/**
 * Function prototypes for application
 */
int *genRandomIntegerNumbers(int lowerRange, int upperRange, int count);
int isNumber(char value[]);
int compareA(const void *val1, const void *val2);
int compareB(const void *val1, const void *val2);
void printArray(const char *narr, int *arr, int length);
int checkShMemName(char *name);
int createSharedMemoryObject(char *name, int arrSize);
data_share_t *mapSHMObject(int fd, int arrSize);
void unMapClose(data_share_t *data, int arrSize, int fd);
