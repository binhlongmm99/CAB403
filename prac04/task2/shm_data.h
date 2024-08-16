/**
 * Data structures for application
 */

/**
 * struct that contains an array of integers that will
 * be used to represent the shared memory object created
 */
typedef struct sm_data
{
    int arrSize;
    int arrayData[];
} data_share_t;

/**
 * Narrations used to prepend output from the application when
 * writing out the integers store in data_share_t
 */
const char *pre = "Child Operation: Original sequence: ";
const char *postAC = "Child Operation: Sorted sequence ASC: ";
const char *postPA = "Parent Operation: Current sequence: ";
const char *postPD = "Parent Operation: Sorted sequence DEC: ";