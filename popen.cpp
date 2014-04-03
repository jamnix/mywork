#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "fcntl.h"

#define BUFSIZE 1024

int main()
{
	FILE* fp;
	char *cmd = "ps -ef";
	char buf[BUFSIZE];
	buf[BUFSIZE] = '\0';
	if((fp = popen(cmd, "r")) == NULL)
	{
		printf("error");
	}
	else
	{
		while((fgets(buf, BUFSIZE, fp)) != NULL)
		{
			printf("%s",buf);
		}
		pclose(fp);
	}
	return 0;
}

