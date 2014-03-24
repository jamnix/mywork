#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include "errno.h"
#include "strings.h"
#include "unistd.h"

int SERV_PORT = 1935;
int LISTENQ = 4096;
int MAXLINE = 128;

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

	while(1)
	{
		if( (n = read(sockfd, buf, MAXLINE)) > 0)
		{
			ssize_t nwrite;
			const char* w_ptr;
			w_ptr = buf;
			while(n > 0)
			{
				if((nwrite = write(sockfd, w_ptr, n)) <= 0)
				{
					if(nwrite < 0 && errno == EINTR)
						nwrite = 0;
					else
					{
						printf("write error");
						break;
					}
				}
				n -= nwrite;
				w_ptr += nwrite;
			}
		}
		else if(n < 0)
		{
			if(errno == EINTR)
				continue;
			else
			{	
				printf("error");
				break;
			}
		}
		else if(n == 0)
		{	
			printf("finish");
			break;
		}
	}
	
}

int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr));
	
	listen(listenfd, LISTENQ);

	for( ; ; )
	{
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (sockaddr*)&cliaddr, &clilen);
		
		if( (childpid = fork()) == 0)
		{
			close(listenfd);
			str_echo(connfd);
			//close(connfd);
		}
		close(connfd);
	}
}
