#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"

short SERV_PORT = 8080;
int MAXLINE = 128;

void dg_echo(int sockfd, sockaddr* cliaddr, socklen_t clilen)
{
	int n;
	socklen_t len;
	char msg[MAXLINE];
	
	for(;;)
	{
		len = clilen;
		n = recvfrom(sockfd, msg, sizeof(msg), 0, cliaddr, &len);
		sendto(sockfd, msg, n, 0, cliaddr, len);
	}
}

int main()
{
	int sockfd;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
	
	dg_echo(sockfd, (sockaddr*)&cliaddr, sizeof(cliaddr));
	
}
