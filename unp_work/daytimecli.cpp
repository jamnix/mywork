#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int MAXLINE = 4096;
int main(int argc, char **argv)
{
        int sockfd, n;
        char recvline[MAXLINE + 1];
        struct sockaddr_in servaddr;

        if (argc != 2)
        {
                printf("usage: a.out <ipadress>");
                exit(1);
        }

        if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                printf("socket error");
                exit(1);
        }

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;

        servaddr.sin_addr.s_addr = inet_addr(argv[1]);
        servaddr.sin_port = htons(8000);

        if( connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        {
                printf("connect error");
                exit(1);
        }

        while( (n = read(sockfd, recvline, MAXLINE)) > 0)
        {
                recvline[n] = 0;
                printf("%s", recvline);
        }

        if (n < 0)
		printf("read error");

	return 0;

}
