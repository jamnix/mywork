#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "fcntl.h"

int main()
{
	int fd;
	char w_buf[100] = "fuckyoutooooooooooooooo";
	fd = open("/tmp/myfifo", O_WRONLY|O_NONBLOCK, 0);
	if(fd == -1)
		if(errno == ENXIO)
		{
			printf("no read process");
			return -1;
		}
	printf("fd %d", fd);
	int nwrite;
	if((nwrite = write(fd, w_buf, 100)) == -1)
		if(errno == EAGAIN)
			printf("not ready");
	else
		printf("write to fifo %d", nwrite);
	printf("end %d", nwrite);
}

