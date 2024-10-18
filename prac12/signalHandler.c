#include <stdio.h>
#include <signal.h>

void signalHandler(int sig);
 
int main(){
    signal(SIGINT, signalHandler);
    while(1);
    return 0;
}

void signalHandler(int sig){
    printf("Received Ctrl+C. Quiting!\n");
}