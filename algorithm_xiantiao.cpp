#include "iostream"
using namespace std;

int main()
{
	int s[10] = {2,3,4,5,6,7,8,9,10,11};
	int f[10] = {3,5,7,6,9,8,12,10,13,15};

	int tol = 3-2;
	int begin = 2;
	int end = 3;

	for(int i=1; i<10; i++)
	{
		if(s[i] >= end)
		{
			tol += f[i] - s[i];
			begin = s[i];
			end = f[i];
		}
		else if(f[i] > end)
		{
			tol += f[i] - end;
			end = f[i];
		}
		else
			continue;
	}
	cout << tol;
}
