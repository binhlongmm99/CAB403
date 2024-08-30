#include <pthread.h>
#include <stdio.h>

void *addMillion(void *arg);
int globalVar =0;
pthread_mutex_t lock;

int main(int argc, char *argv[]) {
	pthread_mutex_init(&lock, NULL);
	pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, addMillion, NULL);
    pthread_create(&thread2, NULL, addMillion, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);   
    printf("\n\nTotal for globalVar = %d\n", globalVar);
    pthread_mutex_destroy(&lock);
    return 0;
}

void *addMillion(void *ptr) {	
	if (pthread_mutex_lock(&lock) != 0) {
        fprintf(stderr, "Error with mutex lock\n");
		// perror("\nError with mutex lock\n");
	}
    for (int i = 0; i < 1000000; i++) {
        globalVar++;
    }         
    if (pthread_mutex_unlock(&lock)) {
        fprintf(stderr, "Error unlocking mutex\n");
		// perror("\nError unlocking mutext\n");
	}
    return NULL;
}
