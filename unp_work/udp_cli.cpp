#include "stdlib.h"
#include "stdio.h"
#include "arpa/inet.h"
#include "string.h"

short PORT = 8080;
int MAXLINE = 128;

void dg_cli(FILE* in_stream, int sockfd, sockaddr* servaddr, socklen_t len)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE];
	
	while(fgets(sendline, MAXLINE, in_stream))
	{
		sendto(sockfd, sendline, strlen(sendline), 0, servaddr, len);
		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		recvline[n] = 0;
		fputs(recvline, stdout);
		sockaddr_in * tmp = (sockaddr_in*)servaddr;
		//tmp->sin_family = AF_UNSPEC;
		//connect(sockfd, servaddr, len);
	}
}


int main()
{
	int sockfd;
	socklen_t clilen;
	struct sockaddr_in servaddr, cliaddr;
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
	getsockname(sockfd, (sockaddr*)&cliaddr, &clilen);
	printf("%s", inet_ntoa(cliaddr.sin_addr.s_addr));
	dg_cli(stdin, sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
}
