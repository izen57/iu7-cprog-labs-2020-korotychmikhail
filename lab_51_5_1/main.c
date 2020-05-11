#include <stdio.h>
#define SUCCESS 0
#define INCORECT_INPUT -1
#define IMPOSSIBLE_CONDITION -2
int process(FILE *file, int *max)
{
	int count = 1, prev, curr;
	if (fscanf(file, "%d", &prev) == 1)
	{
		int flag1 = 0, flag2 = 0;
		while (fscanf(file, "%d", &curr) == 1)
		{
			flag1 = 1;
			if (curr == prev)
			{
				count++;
				flag2 = 1;
			}
			else
				count = 1;
			if (count > *max)
				*max = count;
			prev = curr;
		}
		if (!flag1)
			return INCORECT_INPUT;
		if (!flag2)
			return IMPOSSIBLE_CONDITION;
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