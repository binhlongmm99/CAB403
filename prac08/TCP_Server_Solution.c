#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1023

int main(int argc, char **argv)
{

	/* client file descriptor */
	int clientfd;
	/* receive buffer */
	char buffer[BUFFER_SIZE];

	struct sockaddr clientaddr;
	socklen_t addrlen;

	/* Check user has passed in the port number at the command line
	 * local host will be used as the default address
	 */
	if (argc != 2)
	{
		printf("Correct usage: TCPServer <port number>\n");
		return -1;
	}

	/* Create a TCP/IP socket making sure to select appropriate family, communication type &
	 * protocol
	 */
	int fd = socket(AF_INET, SOCK_STREAM, 0); // 0 is default for socket implementation
	if (fd == -1)
	{
		perror("Error in creating socket\n");
		// fprintf(stderr, "Error in creating socket\n");
		return 1;
	}

	/* Declare a data structure to specify the socket address (IP Address + Port)
	 * Complete the Internet socket address structure
	 * An IPv4 socket address structure - use memset to zero the struct out
	 */

	struct sockaddr_in serverAddress;
	memset(&serverAddress, '\0', sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(atoi(argv[1]));

	/* Assign a name to the socket created - Implement bind() system call */
	if (bind(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
	{
		perror("Error in bind()");
		return 1;
	}

	/* Place server in passive mode - listen for incomming client request  */
	if (listen(fd, 10) == -1)
	{
		perror("Error in listen()");
		return 1;
	}

	/* infinite loop */
	while (1)
	{

		/*  Generate a new socket for data transfer with the client */
		clientfd = accept(fd, &clientaddr, &addrlen);
		if (clientfd == -1)
		{
			perror("Error in accept()");
			return 1;
		}

		/* receive the incomming client data */
		int bytesRecv = recv(clientfd, buffer, 1023, 0);
		if (bytesRecv == -1)
		{
			perror("Error in recv()");
			return 1;
		}

		/* add null terminator to received data and print out message */
		buffer[bytesRecv] = '\0';
		printf("\nNumber of Bytes receive: %d\n", bytesRecv);
		printf("Message: %s\n", buffer);

		/* close the socket used to receive data */
		close(clientfd);

	} // end while

	/* shutdown the connection - end communication to and drom the socket SHUT_RDWR */
	if (shutdown(clientfd, SHUT_RDWR) == -1)
	{
		perror("Error in shutdown()");
		return 1;
	}

	/* sockets can remain open after program termination */
	close(fd);
}

// echo Hello Server | nc localhost 5555