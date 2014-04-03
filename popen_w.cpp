#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "fcntl.h"
#include "string.h"

#define BUFSIZE 1024

int main()
{
	FILE* fp;
	char *cmd = "cat > xxx";
	char buf[BUFSIZE];
	buf[BUFSIZE] = '\0';
	if((fp = popen(cmd, "w")) == NULL)
	{
		printf("error");
	}
	else
	{
		fwrite(cmd, strlen(cmd), 1, fp);
		pclose(fp);
	}
	return 0;
}

