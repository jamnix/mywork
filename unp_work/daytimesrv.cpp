#include  "time.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include "stdlib.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "signal.h"

int LISTENQ = 1024;
int MAXLINE = 4096;


int main(int argc, char** argv)
{

	pid_t pid;
	if((pid = fork()) < 0)
		return -1;
	else if(pid)
		exit(0);

	if(setsid() < 0)
		return -1;

	signal(SIGHUP, SIG_IGN);
	
	if((pid = fork()) < 0)
		return -1;
	else if(pid)
		exit(0);
	
	chdir("/");
	umask(002);

	for(int i=0; i < 64; i ++)
		close(i);


	int fd = open("/dev/null", O_RDWR, 0);
	if(fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		if(fd > 2)
			close(fd);
	}

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
	
