#include "iostream"
//#include "stdlib.h"


int main()
{
	const int a = 1;
	int *p = const_cast<int*>(&a);
	*p = 2;
	//printf("%d, %d", a , *p);
	std::cout<< a << std::endl << *p;
}
