#include "sys/msg.h"
#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"

#define BUFSIZE 256

struct msg_st
{
	long int msg_type;
	char text[BUFSIZE];
};

int main()
{
	int running = 1;
	int msgid = -1;
	struct msg_st data;
	long int msgtype = 0;

	msgid = msgget((key_t)1234, 0666| IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget error, errno:%d", errno);
		return -1;
	}
	while(running)
	{
		if(msgrcv(msgid, (void*)&data, BUFSIZE, msgtype, 0) == -1)
		{
			fprintf(stderr, "msgrcv failed, errno: %d", errno);
			return -1;
		}
		printf("you write: %s\n", data.text);
		if(strncmp(data.text, "end", 3) == 0)
			running = 0;
	}
	if(msgctl(msgid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) error\n");
		return -1;
	}
	return 0;
		
}
