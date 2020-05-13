#include <stdio.h>
#include "functions.h"
int avg_function(FILE *file, float *avg, int *count)
{
	float num, sum = 0;
	while (fscanf(file, "%f", &num) == 1)
	{
		sum += num;
		(*count)++;
	}
	if (!*count)
		return INCORRECT_INPUT;
	else
	{
		*avg = sum / *count;
		return SUCCESS;
	}
}
void disp_function(FILE *file, float *disp, float avg, int count)
{
	float num, sum = 0;
	for (int i = 0; i < count; i++)
	{
		fscanf(file, "%f", &num);
		sum += (num - avg) * (num - avg);
	}
	*disp = sum / count;
}