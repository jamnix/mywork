#include "iostream"
using namespace std;


int main()
{
	int aa[]={1, 2, 3, 4, 5, 6};
	int bb[]={7,8,9,10};
	//int a = 1;
	int *p = bb-2;
	cout << sizeof(int*) << endl;
	cout << aa <<endl;
	cout << bb << endl;
	//cout << &a << endl;
	cout << &p << endl;
	
	cout << p << endl;
	cout << hex << *p <<endl;
	//cout << int(p) << endl;

}
