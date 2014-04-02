#include "iostream"
using namespace std;

int main()
{
	int maxColors = 0, i, j, k;
	for(i = 0; i < N; i++)
	{
		for(j=0;j<maxColors;j++)
			isForbidden[j] = false;
		for(j=0;j<i;j++)
		{
			if(overlap(j,i))
				isForbidden[color[j]] = true;
		}
		for(j=0;j<maxColors;j++)
		{
			if(!isForbidden[j])
				break;	
		}
		if(j < maxColors)
			color[i] = j;
		else
			color[i] = maxColors++; 
	}
	return maxColors;
}
