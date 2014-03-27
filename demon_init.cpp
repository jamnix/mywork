#include "iostream"

int main()
{
	pid_t pid;
	if((pid = fork()) < 0)
		return -1;
	else if(pid)
		exit(1);

	if (setsid() < 0)
		return -1;
}
