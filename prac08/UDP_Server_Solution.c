#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 1023

int main(int argc, char **argv)
{

	/* check port number is passed in on command line */
	if (argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		return 1;
	}

	int sockfd;
	struct sockaddr_in server_addr, client_addr;
	char buffer[BUFFER_SIZE];
	socklen_t addr_size;
	char *ip = "127.0.0.1";
	char *end = "Closing connection to the server.\n";
	char *std = "Message received successfully\n";

	/* Create a UDP Socket */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror("Error in creating socket\n");
		return 1;
	}

	/* Initialise the sockaddr_in structure
	 * use memset to zero the struct out
	 */
	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[1]));
	server_addr.sin_addr.s_addr = inet_addr(ip);

	/* bind server address to socket descriptor */
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("Error in bind()");
		return 1;
	}
	bool cont = true;
	while (cont)
	{

		/* clear buffer */
		bzero(buffer, BUFFER_SIZE);
		/* Calculating the Client Datagram length */
		addr_size = sizeof(client_addr);
		/* use recvfrom to receive data from client */
		int messageSize = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_size);
		buffer[messageSize] = '\0';

		/* check end connection message sent */
		if (strncasecmp(buffer, "q", 1) == 0)
		// if (strcmp(buffer, "q") == 0)
		{
			printf("Closing socket\n");
			cont = false;
		}

		/* Output the message from the client */
		printf("Data receive: %s\n", buffer);

		/* Clear the buffer and send a message from the server to the client */
		bzero(buffer, BUFFER_SIZE);
		if (cont)
		{
			strcpy(buffer, std);
		}
		else
		{
			strcpy(buffer, end);
			printf("Closing socket\n");
		}
		sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
		printf("Data send: %s\n", buffer);
	}

	// Closing the Socket File Descriptor.
	close(sockfd);
	return 0;
}

// nc -u localhost 5555