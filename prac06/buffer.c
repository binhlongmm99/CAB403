#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define TRUE 1

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insertPointer = 0, removePointer = 0;

void *producer(void *param);
void *consumer(void *param);

int insert_item(buffer_item item)
{
	int fullValue = 0, emptyValue = 0;
	// Acquire Empty Semaphore
	sem_wait(&empty); // 5 -> 4

	// Acquire mutex lock to protect buffer
	pthread_mutex_lock(&mutex);
	printf("\nStarting to produce\n");
	sem_getvalue(&full, &fullValue);
	sem_getvalue(&empty, &emptyValue);
	printf("Value of full semaphore = %d\n", fullValue);
	printf("Value of empty semaphore = %d\n", emptyValue);

	buffer[insertPointer++] = item;
	insertPointer = insertPointer % BUFFER_SIZE;

	// Release mutex lock and full semaphore
	pthread_mutex_unlock(&mutex);
	sem_post(&full); // 0 -> 1
	printf("\nFinished producing\n");
	sem_getvalue(&full, &fullValue);
	sem_getvalue(&empty, &emptyValue);
	printf("Value of full semaphore = %d\n", fullValue);
	printf("Value of empty semaphore = %d\n", emptyValue);

	return 0;
}

int remove_item(buffer_item *item)
{
	int fullValue = 0, emptyValue = 0;
	// Acquire Full Semaphore
	sem_wait(&full);

	// Acquire mutex lock to protect buffer
	pthread_mutex_lock(&mutex);
	printf("\nStarting to consuming\n");
	sem_getvalue(&full, &fullValue);
	sem_getvalue(&empty, &emptyValue);
	printf("Value of full semaphore = %d\n", fullValue);
	printf("Value of empty semaphore = %d\n", emptyValue);

	*item = buffer[removePointer];
	buffer[removePointer++] = -1;
	removePointer = removePointer % BUFFER_SIZE;

	// Release mutex lock and empty semaphore
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	printf("\nFinished consuming\n");
	sem_getvalue(&full, &fullValue);
	sem_getvalue(&empty, &emptyValue);
	printf("Value of full semaphore = %d\n", fullValue);
	printf("Value of empty semaphore = %d\n", emptyValue);

	return 0;
}

int main(int argc, char *argv[])
{
	int sleepTime, producerThreads, consumerThreads;
	int fullValue = 0, emptyValue = 0;

	if (argc != 4)
	{
		fprintf(stderr, "Useage: <sleep time> <producer threads> <consumer threads>\n");
		return -1;
	}

	sleepTime = atoi(argv[1]);
	producerThreads = atoi(argv[2]);
	consumerThreads = atoi(argv[3]);

	pthread_t prod_list[producerThreads];
	pthread_t cons_list[consumerThreads];

	// Initialize the locks
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);
	srand(time(0));

	sem_getvalue(&full, &fullValue);
	sem_getvalue(&empty, &emptyValue);
	printf("Value of full semaphore = %d\n", fullValue);
	printf("Value of empty semaphore = %d\n", emptyValue);

	// Create the producer and consumer threads
	for (int i = 0; i < producerThreads; i++)
	{
		pthread_create(&prod_list[i], NULL, producer, NULL);
	}

	for (int j = 0; j < consumerThreads; j++)
	{
		pthread_create(&cons_list[j], NULL, consumer, NULL);
	}

	// //Join the producer and consumer threads
	// for (int i = 0; i < producerThreads; i++){
	//     pthread_join(prod_list[i], NULL);
	// }
	// for (int j = 0; j < consumerThreads; j++){
	//     pthread_join(cons_list[j], NULL);
	// }

	pthread_mutex_destroy(&mutex);
	sleep(sleepTime);

	return 0;
}

void *producer(void *param)
{
	buffer_item random;
	int r;

	while (TRUE)
	{
		r = rand() % 5;
		sleep(r);
		random = rand();

		if (insert_item(random))
			fprintf(stderr, "Error");

		printf("Producer produced %d \n", random);
	}
}

void *consumer(void *param)
{
	buffer_item random;
	int r;

	while (TRUE)
	{
		r = rand() % 5;
		sleep(r);

		if (remove_item(&random))
			fprintf(stderr, "Error Consuming");
		else
			printf("Consumer consumed %d \n", random);
	}
}
