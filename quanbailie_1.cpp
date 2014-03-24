#include "stdio.h"
#include "stdlib.h"
#include "string.h"


int compare(const void* a, const void* b)
{
	return *(char*)a - *(char*)b;
}

void quanpailie(char* input, int len)
{
	qsort(input, len, sizeof(char), compare);
	printf("%s\n", input);
	while(1)
	{
		bool flag = false;
		int index;
		int swap_index;
		for(int i=len-1; i>=1; i--)
		{
			if(input[i] > input[i-1])	
			{
				index = i-1;	
				swap_index = i;
				flag = true;
				break;
			}
		}
		if(!flag)
			break;
		for(int i=swap_index+1; i<len; i++)
		{
			if(input[i] <= input[swap_index] && input[i] > input[index])
				swap_index = i;
		}
		char tmp = input[index];
		input[index] = input[swap_index];
		input[swap_index] = tmp;
		printf("%s\n", input);
	}
}



int main(int argc, char* argv[])
{
	char* input = argv[1];
	quanpailie(input, strlen(input));
}
