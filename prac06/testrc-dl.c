#include <pthread.h>
#include <stdio.h>

int globalVar = 0;

void *addMillion(void *arg);

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, addMillion, NULL);
    pthread_create(&thread2, NULL, addMillion, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("\n\nTotal for globalVar = %d\n", globalVar);
    return 0;
}

void *addMillion(void *arg) {   
    for (int i = 0; i < 1000000; i++) {
        globalVar++;
    }    
    return NULL;
}