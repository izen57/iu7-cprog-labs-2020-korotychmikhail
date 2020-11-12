#include <stdio.h>
#include <stdlib.h>
#include "../inc/error_codes.h"
int counting_numbers(FILE *file, int *n)
{
	int number, error = SUCCESS;
	for (int i = 0; !feof(file); i++)
	{
		if (fscanf(file, "%d", &number) == 1)
			(*n)++;
		else
		{
			error = READ_ERROR;
			break;
		}
	}
	return error;
}
int read_array(FILE *file, int **begin, int **end)
{
	int error = SUCCESS;
	while (!feof(file))
	{
		fscanf(file, "%d", *end);
		(*end)++;
	}
	if (*begin == *end)
	{
		free(begin);
		error = READ_ERROR;
	}
	return error;
}
void output(FILE *file, int *begin, int *end)
{
	for (int *i = begin; i < end; i++)
		fprintf(file, "%d ", *i);
}