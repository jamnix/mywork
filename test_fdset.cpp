#include "unistd.h"
#include "sys/select.h"
#include "iostream"
#include "sys/socket.h"


int main(int argc, char** argv)
{
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(STDOUT_FILENO, &fdset);

	if(FD_ISSET(STDOUT_FILENO, &fdset) != 0)
		std::cout<<"STDOUT set";
	else
		std::cout<<"STDOUT not set";
	
	FD_CLR(STDOUT_FILENO, &fdset);
	
	if(FD_ISSET(STDOUT_FILENO, &fdset) != 0)
		std::cout<<"STDOUT set";
	else
		std::cout<<"STDOUT not set";


	int num = 3000;
	for(int i=0; i< num; i++)
	{
		std::cout<<"*[" << i << "]";
		std::cout << "fd : " << i << std::endl;
		FD_SET(i, &fdset);
	}
	
	std::cout<<"done";
}
