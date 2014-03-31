#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "sys/file.h"
using namespace std;

int main()
{
	FILE *fp;
	fp = fopen("./a.txt", "r+b");
	if(fp == NULL)
	{
		cout << "open file error";
		return -1;
	}

	for(int i=0;i<200;i++)
	{
		flock(fp->_fileno, LOCK_EX);
		cout << "aaa, get lock, sleep 5s"<< endl;
		sleep(5);
		flock(fp->_fileno, LOCK_UN);
		cout << "aaa, unlock"<<endl;
	}
}
