#include <stdio.h>
#define SUCCESS 0
#define INCORECT_INPUT -1
int process(FILE *file, int *max)
{
	int count = 1, prev, curr;
	if (fscanf(file, "%d", &prev) == 1)
	{
		int flag = 0;
		while (fscanf(file, "%d", &curr) == 1)
		{
			if (curr == prev)
			{
				count++;
				flag = 1;
			}
			else
				count = 1;
			if (count > *max)
				*max = count;
			prev = curr;
		}
		if (flag)
			return INCORECT_INPUT;
		else
			return SUCCESS;
	}
	else
		return INCORECT_INPUT;
}
int main(void)
{
	int max = 0, error = process(stdin, &max);
	if (!error)
		printf("%d", max);
	return error;
}