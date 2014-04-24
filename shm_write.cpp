#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/shm.h"
#include "sys/ipc.h"
#include "string.h"

struct shared_st {
int write;
char text[100];
};

int main()
{
	key_t key;
	int shmid;
	void* shm;
	struct shared_st * shared;
	key = ftok("/usr/local/include", 'p');
	shmid = shmget(key, sizeof(struct shared_st), 0666| IPC_CREAT);
	shm = shmat(shmid, 0, 0);
	if(shm == (void*)-1)
	{
		printf("shmat error");
	}
	
	shared = (struct shared_st*) shm;
	memcpy(shared->text, "sfsfsdf", 7);
	if(shmdt(shm) == -1)
		return -1;
}
