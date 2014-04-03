#include <pthread.h>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

void * thread(void* argc)
{
	printf("hello");
}


int main()
{
	pthread_t id;
	if(pthread_create(&id, NULL, thread, NULL) != 0)
	{
		printf("create");
	}
	else
		printf("thread");
	sleep(3);

	//pthread_join(id, NULL);
	return 0;
}
