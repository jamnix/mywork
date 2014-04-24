#include "stdio.h"
#include "stdlib.h"
#include "sys/shm.h"
#include "sys/types.h"
#include "sys/ipc.h"

struct shared_st {
int write;
char text[100];
};


int main()
{
	key_t key;
	int shmid;
	void * shm;
	shared_st* shared;
	key = ftok("/usr/local/include", 'p');
	shmid = shmget(key, sizeof(struct shared_st), 0666 | IPC_CREAT);
	if(shmid == -1)
	{
		printf("shmget error");
		return -1;
	}
	shm = shmat(shmid, 0, 0);
	if(shm == (void*)-1)
	{
		printf("shmat error");
		return -1;
	}
	
	shared = (struct shared_st*) shm;
	shared->write = 0;
	printf("%s", shared->text);
	
	if(shmdt(shm) == -1)	
	{
		printf("shmdt error");
		return -1;
	}
	if(shmctl(shmid, IPC_RMID, 0) == -1)
	{
		printf("shmctl error");
		return -1;
	}
	return 0;
}
