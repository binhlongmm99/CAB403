# CAB403 - Practical 2 notes

## Materials

- Makefile: [MIT Makefiles Tutorial](https://web.mit.edu/gnu/doc/html/make_2.html)
- Process creation:
    - [Folk system call](https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html)
    - [Folk in C](https://www.geeksforgeeks.org/fork-system-call/)
- Interprocess communication: [IPC Geeks](https://www.geeksforgeeks.org/inter-process-communication-ipc/)


## Notes
1. The value of fd:
- The value of fd is an array of two integers that represent the file descriptors for the pipe. When you create a pipe using the pipe(fd); function call, the operating system assigns two file descriptors:
    - fd[0]: This is the file descriptor for the read end of the pipe.
    - fd[1]: This is the file descriptor for the write end of the pipe.
The exact integer values assigned to fd[0] and fd[1] depend on the state of the file descriptor table at the time pipe(fd) is called. Typically, they are the lowest available file descriptors not currently in use by the process.

- In typical scenarios, the file descriptors '0', '1', and '2' are reserved for standard input, standard output, and standard error, respectively:
    - '0' is 'stdin' (standard input)
    - '1' is 'stdout' (standard output)
    - '2' is 'stderr' (standard error)
For example:
    - If the lowest available file descriptor is 3, fd[0] might be '3', and fd[1] might be '4'.
    - If you closed some file descriptors before creating the pipe, those freed-up values could be assigned to fd[0] and fd[1].

2. pinGen.c in Task 3:
- You may want to try this:
```
	if (pid > 0)
	{
        close(fd[1]);       //close the write end of the pipe, parent reads only
		close(0);           //Close the standard input (stdin) file descriptor.
		dup(fd[0]);         //Duplicates the file descriptor fd[0] (read end of the pipe) into the lowest available file descriptor
                            //This effectively redirects the standard input to read from the pipe.
        ...
    }
```