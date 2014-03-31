#include "stdio.h"


void str_cli()
{
	
}


int main(int argc, char** argv)
{
	int sockfd;
	struct sockaddr_in servaddr;


	if(argc != 2)
	{
		printf("usage: tcpli <addr>");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SER_PORT);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
	str_cli(stdin, sockfd);
	return 0;
}
