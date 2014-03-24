#include "iostream"
#include "string.h"
#include "stdio.h"
using namespace std;



void quanpailie(char* input, int begin, int end)
{
	if(begin == end)
		printf("%s\n", input);
	else
	{
		for(int i = begin; i <= end; i++)
		{
			if(i != begin && input[begin] == input[i])
				continue;
			char tmp = input[begin];
			input[begin] = input[i];
			input[i] = tmp;
			quanpailie(input, begin+1, end);
			tmp = input[begin];
			input[begin] = input[i];
			input[i] = tmp;
		}
	}
}


int main(int argc, char* argv[])
{
	char* input = argv[1];
	quanpailie(input, 0, strlen(input)-1);
}

