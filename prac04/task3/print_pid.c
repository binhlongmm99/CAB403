/**
 * CAB403 - POSIX Shared Memory Walkthrough
 *
 * Demonstration of the POSIX Semaphore usage for synchronisation
 *
 * Application creates a number of children processes by forking the parent n times.
 * The number of children to create is passed as a command line parameter.
 * The maximum number of children is set to 10.
 * The usage is: ./application_name number_of_children
 */

#include <stdio.h>
#include <stdlib.h>
#include <funcPrototype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#define FALSE 1
#define TRUE 0
#define MAX_CHILD 10
#define SHM_OBJECT "/sem_sm"
#define BUFFER_SIZE 1024
#define USE_DYNAMIC_MEMORY

int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s no_of_children\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (isNumber(argv[1]) == FALSE)
  {
    fprintf(stderr, "usage: %s no_of_children\nno_of_children must be an integer\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (atoi(argv[1]) > MAX_CHILD)
  {
    fprintf(stderr, "usage: %s no_of_children\nno_of_children must be less than %d\n", argv[0], MAX_CHILD);
    exit(EXIT_FAILURE);
  }

#ifdef USE_DYNAMIC_MEMORY
  data_share_t *data = malloc(sizeof(data_share_t));

#else

  int shm_fd = createSharedMemoryObject(SHM_OBJECT);
  if (shm_fd == EXIT_FAILURE)
  {
    fprintf(stderr, "\nError creating shared memory object\n");
    exit(EXIT_FAILURE);
  }
  data_share_t *data = mapSHMObject(shm_fd);
#endif

  splitProcess(atoi(argv[1]), data);

#ifdef USE_DYNAMIC_MEMORY
  free(data);
#else
  unMapClose(data, shm_fd);
#endif

  return EXIT_SUCCESS;
}

/**
 * Function to create the child processes by using fork() - parent will wait until
 * all child processes have completed their work. Child processes created will
 * all execute the work function then exit. Semaphore for synchronisation is
 * initialised in this function and is set to be shared across processes.
 * \param childNumber - then number of children processes to create
 * \param data - pointer to shared memory object/pointer to dynamic memory
 * \returns 0=success else returns 1
 */
int splitProcess(int childNumber, data_share_t *data)
{
  int error;
  sem_init(&(data->child_process_lock), 1, 1);
  pid_t pid[childNumber];
  for (int i = 0; i < childNumber; i++)
  {
    pid[i] = fork();
    if (pid[i] < 0)
    {
      fprintf(stderr, "\nFailed to create children processes: %s\n", strerror(error));
      return EXIT_FAILURE;
    }
    if (pid[i] == 0)
    {
      work(i, data);
      return (EXIT_SUCCESS);
    }
  }
  for (int i = 0; i < childNumber; i++)
  {
    wait(0);
  }

  printf("\n\nAll children done\n");
  return EXIT_SUCCESS;
}

/**
 * Function contains critical section where each child process writes out their PID
 * The PID is stored in a buffer and then printed one char at a time to stdout
 * Note that stdout is set to be not buffered so it will not wait for a newline
 * character before printing to stdout. Critical section marked below
 * \param id - The number of the child created from fork
 * \param data - pointer to shared memory object/pointer to dynamic memory
 */
void work(int id, data_share_t *data)
{

  char *ptr;
  struct timespec sleeptime;
  sleeptime.tv_sec = 0;
  sleeptime.tv_nsec = 10000000L;
  setbuf(stdout, NULL);

  /****************** start of critical section *******************/
  sem_wait(&(data->child_process_lock));
  snprintf(data->buffer, BUFFER_SIZE, "This is child number %d: - Process ID: %d", id, getpid());
  ptr = data->buffer;
  while (*ptr != '\0')
  {
    fputc(*ptr, stdout);
    ptr++;
    nanosleep(&sleeptime, NULL);
  }
  printf("\n");
  sem_post(&(data->child_process_lock));
  /****************** end of critical section *********************/
  return;
}

/**
 * Function to create the shared memory object and size the shared
 * memory object to the correct length (bytes)
 * \param name - name of the shared memory object e.g. /nameOfSMObject
 * \param arrSize - the size of the array containing the random numbers
 * \returns - file descriptor of shared memory object if success else -1
 */
int createSharedMemoryObject(char *name)
{
  shm_unlink(name);
  int fd = shm_open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd == -1)
  {
    return EXIT_FAILURE;
  }
  if (ftruncate(fd, (sizeof(data_share_t))) == -1)
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
data_share_t *mapSHMObject(int fd)
{
  data_share_t *data = mmap(NULL, (sizeof(data_share_t)),
                            PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (data == MAP_FAILED)
  {
    fprintf(stderr, "\nError mapping shared memory object\n");
    exit(EXIT_FAILURE);
  }
  return data;
}

/**
 * Function to remove share memory object mapping and close the file descriptor
 * returned from opening the shared memory object
 * \param data - start address for the mapping
 * \param fd - file descriptor returned from shm_open()
 */
void unMapClose(data_share_t *data, int fd)
{
  munmap(data, (sizeof(data_share_t)));
  close(fd);
}