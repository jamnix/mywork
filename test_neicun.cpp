#include <iostream>
using namespace std;


int* func()
{
	int* a ;
	*a = 1;
	return a;
}

int main()
{
	cout << *func() <<endl;
}
