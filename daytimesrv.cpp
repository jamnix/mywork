#include  "time.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

int LISTENQ = 1024;
int MAXLINE = 4096;


int main(int argc, char** argv)
{
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[MAXLINE];
	time_t ticks;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);
	
	bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr));
	
	listen(listenfd, LISTENQ);
	
	for ( ; ; )
	{
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (sockaddr*)&cliaddr, &len);
		printf("connection from %s, port %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, sizeof(buff));
		close(connfd);
	}
}
	
