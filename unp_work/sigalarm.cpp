#include "stdio.h"
#include "stdlib.h"
#include "signal.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "errno.h"

static void connect_alarm(int signo)
{
	return;
}

int main()
{
	int sockfd,n ;
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = inet_addr("192.168.1.1");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	sighandler_t sigfunc;
	sigfunc = signal(SIGALRM, connect_alarm);
	if(alarm(5) != 0)
		printf("error");
	if(( n = connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr))) < 0)
	{
		close(sockfd);
		if(errno == EINTR)
			errno = ETIMEDOUT;
	}
	alarm(0);
	signal(SIGALRM, sigfunc);
}
