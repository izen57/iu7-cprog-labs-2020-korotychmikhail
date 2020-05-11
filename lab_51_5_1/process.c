#include <stdio.h>
#include "process.h"
int process(FILE *file, int *max)
{
	int count = 1, prev, curr;
	if (fscanf(file, "%d", &prev) == 1)
	{
		while (fscanf(file, "%d", &curr) == 1)
		{
			if (curr == prev)
				count++;
			else
				count = 1;
			if (count > *max)
				*max = count;
			prev = curr;
		}
		return SUCCESS;
	}
	else
		return INCORECT_INPUT;
}