#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

char *message = "This is a message from parent!!!";
char *message2 = "This is a message from child!!!";

int main()
{
    pid_t childpid; /* variable to store the child's pid */
    char buf[1024];
    int fd[2];
    int fd2[2];

    pipe(fd); /* create pipe */
    pipe(fd2); /* create pipe */

    if (fork() != 0)
    { /* Parent code */
        write(fd[1], message, strlen(message) + 1);
        
        read(fd2[0], buf, strlen(message2) + 1);
        printf("I got the following message from my child: %s\n", buf);
    }
    else
    { /* Child code */
		childpid = getpid();
        printf("CHILD: I am the child process!\n");
        printf("CHILD: Here's my PID: %d\n", childpid);
        printf("CHILD: My parent's PID is: %d\n", getppid());

        read(fd[0], buf, strlen(message) + 1);
        printf("I got the following message from my parent: %s\n", buf);
        
        write(fd2[1], message2, strlen(message2) + 1);
    }
    return 0;
}

