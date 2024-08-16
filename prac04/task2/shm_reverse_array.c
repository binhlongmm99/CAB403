/**
 * CAB403 - POSIX Shared Memory Walkthrough
 *
 * Demonstration of the creation of a POSIX shared memory object.
 *
 * Application to generate an array of random integers and sort them into non-descending order
 * or non-ascending order depending if child/parent process.
 * The sorted random numbers will be stored in an array which is part of the data
 * structure defined in shm_data.h. This data structure represents the shared memory object
 * and will be used to access the shared memory.
 * Four parameters should be passed at the command line when running application.
 * Format to run application "./app_name shm_name lower upper count"
 * \shm_name: shared memory object name
 * \lower: lowest value for random number
 * \upper: highest value for random number
 * \count: amount of random numbers to create
 *
 * The shared memory object will be mapped to the process before calling fork() to
 * create a child process. The child will inherit the shared memory identifier and
 * mapped memory object.The child will create an array of integers and then sort them
 * into non-descending order. This data will then be stored in the shared memory object
 * created by the parent process. The child should print the sorted array to the terminal and exit.
 * The parent will wait until the child has exited then will confirm the array has
 * been sorted by printing the array stored in the shared memory object. Parent will then sort
 * the array stored in the shared memory object into non-ascending order and print out the sequence
 * of numbers from the shared memory object.
 * Parent will then remove the shared memory object and exit.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <shm_data.h>
#include <stdbool.h>
#include <protoHeader.h>
#include <unistd.h>
#include <sys/wait.h>
#define FALSE 1
#define TRUE 0
#define ASC 0
#define DEC 1

int main(int argc, char *argv[])
{
  if (argc != 5)
  {
    fprintf(stderr, "usage: %s shm_name lower_range upper_range count\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if ((isNumber(argv[2]) == FALSE) || (isNumber(argv[3]) == FALSE) || (isNumber(argv[4]) == FALSE))
  {
    fprintf(stderr, "usage: %s shm_name lower_range upper_range count\nlower_range and upper_range and count must be integers\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (checkShMemName(argv[1]) == FALSE)
  {
    fprintf(stderr, "usage: %s is not a valid name for shared memory object\nmust start with '/'\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  int shm_fd = createSharedMemoryObject(argv[1], atoi(argv[4]));
  if (shm_fd == EXIT_FAILURE)
  {
    fprintf(stderr, "\nError creating shared memory object\n");
    exit(EXIT_FAILURE);
  }

  data_share_t *data = mapSHMObject(shm_fd, atoi(argv[4]));
  data->arrSize = atoi(argv[4]);

  pid_t child_pid = fork();
  if (child_pid == 0)
  {

    int *ranArrValues = genRandomIntegerNumbers(atoi(argv[2]), atoi(argv[3]), data->arrSize);

    for (int i = 0; i < data->arrSize; i++)
    {
      data->arrayData[i] = ranArrValues[i];
    }
    free(ranArrValues);
    printArray(pre, data->arrayData, data->arrSize);
    qsort(data->arrayData, data->arrSize, sizeof(int), compareA);
    printArray(postAC, data->arrayData, data->arrSize);
    unMapClose(data, data->arrSize, shm_fd);
    return 0;
  }
  else
  {
    wait(NULL);
    printArray(postPA, data->arrayData, data->arrSize);
    qsort(data->arrayData, data->arrSize, sizeof(int), compareB);
    printArray(postPD, data->arrayData, data->arrSize);
    unMapClose(data, data->arrSize, shm_fd);
    // shm_unlink (argv[1]);
  }
  return EXIT_SUCCESS;
}

/**
 * Function to remove share memory object mapping and close the file descriptor
 * returned from opening the shared memory object
 * \param data - start address for the mapping
 * \param arrSize - the size of the array
 * \param fd - file descriptor returned from shm_open()
 */
void unMapClose(data_share_t *data, int arrSize, int fd)
{
  munmap(data, (sizeof(data_share_t) + sizeof(int) * arrSize));
  close(fd);
}

/**
 * Function to create the shared memory object and size the shared
 * memory object to the correct length (bytes)
 * \param name - name of the shared memory object e.g. /nameOfSMObject
 * \param arrSize - the size of the array containing the random numbers
 * \returns - file descriptor of shared memory object if success else -1
 */
int createSharedMemoryObject(char *name, int arrSize)
{
  shm_unlink(name);
  int fd = shm_open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1)
  {
    return EXIT_FAILURE;
  }
  if (ftruncate(fd, (sizeof(data_share_t) + sizeof(int) * arrSize)) == -1)
  {
    return EXIT_FAILURE;
  }
  return fd;
}

/**
 * Function to map the shared memory object to virtual address space of the calling process
 * \param fd - file descriptor returned from creating shared memory object
 * \param arrSize - the length of the array that contains the random integers generated
 * \returns - pointer/address used for mapping that can be used to modify data in shared memory object
 *          - returns MAP_FAILED if the mapping fails
 */
data_share_t *mapSHMObject(int fd, int arrSize)
{
  data_share_t *data = mmap(NULL, (sizeof(data_share_t) + sizeof(int) * arrSize), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (data == MAP_FAILED)
  {
    fprintf(stderr, "\nError mapping shared memory object\n");
    exit(EXIT_FAILURE);
  }
  return data;
}