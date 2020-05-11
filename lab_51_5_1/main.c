#include <stdio.h>
#define success 0
#define incorrect_input -1
int process(FILE *file, int *max)
{
	int count = 1, prev, curr;
	if (fscanf(file, "%d", &prev) == 1)
	{
		int flag = 0;
		while (fscanf(file, "%d", &curr) == 1)
		{
			flag = 1;
			if (curr == prev)
				count++;
			else
				count = 1;
			if (count > *max)
				*max = count;
			prev = curr;
		}
		if (!flag || *max == 1)
			*max = 0;
		return success;
	}
	else
		return incorrect_input;
}
int main(void)
{
	int max = 0;
	int error = process(stdin, &max);
	if (!error)
		printf("%d", max);
	return error;
}