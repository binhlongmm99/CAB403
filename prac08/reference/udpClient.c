#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SERV_PORT 3000
#define MAXLINE 250
int main()
{
    int sockfd, n, from_len;
    struct sockaddr_in servaddr, from_socket;
    socklen_t addrlen = sizeof(from_socket);
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    FILE *fp;

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Create socket!\n");

    while (fgets(sendline, MAXLINE, stdin) != NULL)
    {
        printf("To Server: %s", sendline);
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *)&from_socket, &addrlen);
        recvline[n] = 0; // null terminate
        printf("From Server: %s %d %s", inet_ntoa(from_socket.sin_addr), htons(from_socket.sin_port), recvline);
    }
}