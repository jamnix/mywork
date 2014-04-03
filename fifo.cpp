#include "sys/types.h"
#include "sys/stat.h"
#include "errno.h"
#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#define FIFO "/tmp/myfifo"

int main()
{
	char buf_r[100];
	int fd;
	int nread;
	if((mkfifo(FIFO, O_CREAT|O_EXCL)) < 0 && (errno != EEXIST))
	{
		printf("cannot create fifo");
	}
	memset(buf_r, 0, sizeof(buf_r));
	fd = open(FIFO, O_RDONLY|O_NONBLOCK, 0);
	if(fd == -1)
	{
		printf("error");
		return -1;
	}
	while(1)
	{
		memset(buf_r, 0, sizeof(buf_r));
		if((nread = read(fd, buf_r, 100)) == -1)
		{
			if(errno == EAGAIN)
				printf("no data");
		}
		printf("read %d, %s from fifo\n", nread, buf_r);
		sleep(1);
	}
	pause();
	unlink(FIFO);
}
