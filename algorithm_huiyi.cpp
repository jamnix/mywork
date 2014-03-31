#include "iostream"
using namespace std;



void func()
{
	for()
}


int main()
{
	int s[11] = {1,3,0,5,3,5,6,8,8,2,12};
	int f[11] = {4,5,6,7,8,9,10,11,12,13,14};
	
	bool mark[11] = {0};
	int j=0;
	mark[0] = true;

	

	for(int i=1; i<11; i++)
	{
		if(s[i] >= f[j])
		{
			j=i;
			mark[i]=true;
		}
	}

	for(int i=0; i<11; i++)
		if(mark[i])
			cout << s[i] << " " << f[i] << " ";


}
