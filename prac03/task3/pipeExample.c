#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

char *message = "This is a message from parent!!!";

int main()
{
    pid_t childpid; /* variable to store the child's pid */
    char buf[1024];
    int fd[2];
    pipe(fd); /* create pipe */
    if (fork() != 0)
    { /* I am the parent */
        write(fd[1], message, strlen(message) + 1);
    }
    else
    { /* Child code */
        childpid = getpid();
        printf("CHILD: I am the child process!\n");
        printf("CHILD: Here's my PID: %d\n", childpid);
        printf("CHILD: My parent's PID is: %d\n", getppid());

        read(fd[0], buf, strlen(message) + 1);
        printf("I got the following message from my parent: %s\n", buf);
    }
    return 0;
}
