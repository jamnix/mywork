#include "unistd.h"
#include "errno.h"
#include "stdio.h"
#include "string.h"
#include "sys/msg.h"

#define BUFSIZE 256

struct msg_st
{
	long int msg_type;
	char text[BUFSIZE];
};


int main()
{
	int running = 1;
	struct msg_st data;
	char buf[BUFSIZE];
	int msgid = -1;

	msgid = msgget((key_t)1234, 0666|IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget errno: %d", errno);
		return -1;
	}
	
	while(running)
	{
		printf("enter text:");
		fgets(buf, BUFSIZE, stdin);
		data.msg_type = 1;
		strcpy(data.text, buf);
		if(msgsnd(msgid, (void*)&data, BUFSIZE, 0) == -1)
		{
			fprintf(stderr, "msgsnd error\n");
			return -1;
		}
		if(strncmp(buf, "end", 3) == 0)
			running = 0;
		sleep(2);
	}
	return 0;
}
