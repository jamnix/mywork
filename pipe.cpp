#include "unistd.h"
#include "memory.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/wait.h"

int main()
{
int pipe_fd[2];
pid_t pid;
char buf_r[100];
int r_num;
int n;

memset(buf_r, 0, sizeof(buf_r));
if(pipe(pipe_fd) < 0)
{
	printf("pipe create error\n");
	return -1;
}
if((pid = fork()) == 0)
{
	close(pipe_fd[1]);
	if((r_num = read(pipe_fd[0], buf_r, 100)) > 0)
	{
		printf("%s", buf_r);
	}
	close(pipe_fd[0]);
	return 0;
}
else if(pid > 0)
{
	close(pipe_fd[0]);
	if(write(pipe_fd[1],"hello", 5) != -1)
		printf("parent write suc\n");
	sleep(1);
	if((n = write(pipe_fd[1], "pipe", 5)) != -1)
		printf("parent write suc\n");
	else
	{
		printf("%d, error: %d", n, errno);
	}
	close(pipe_fd[1]);
	sleep(3);
	waitpid(pid, NULL, 0);
	return 0;
}
}
