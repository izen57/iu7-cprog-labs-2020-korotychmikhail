#include <stdio.h>
#include <stdlib.h>
#include "../inc/key.h"
#include "../inc/mysort.h"
int counting_numbers(FILE *file, int *n)
{
	int number, error = 0;
	for (int i = 0; !feof(file); i++)
	{
		if (fscanf(file, "%d", &number) == 1)
			(*n)++;
		else
		{
			error = 1;
			break;
		}
	}
	return error;
}
int read_array(FILE *file, int **begin, int **end)
{
	int error = 0;
	while (!feof(file))
	{
		fscanf(file, "%d", *end);
		(*end)++;
	}
	if (*begin == *end)
	{
		free(begin);
		error = 1;
	}
	return error;
}
void output(FILE *file, int *begin, int *end)
{
	for (int *i = begin; i < end; i++)
		fprintf(file, "%d ", *i);
}
int main(int argc, char **argv)
{
	int error = 0;
	if (argc == 3 || argc == 4)
	{
		FILE *in_file = fopen(argv[1], "r");
		if (in_file)
		{
			int n = 0;
			if (!counting_numbers(in_file, &n))
			{
				rewind(in_file);
				int *arr = calloc(n, sizeof(int));
				int *end = arr;
				if (!read_array(in_file, &arr, &end))
				{
					fclose(in_file);
					int *newarr, *pointer = arr, count = n, *endpointer = end, *endnewarr = newarr;
					if (argc == 4)
					{
						if (!key(arr, end, &newarr, &endnewarr))
						{
							pointer = newarr;
							endpointer = endnewarr;
							count = 0;
							for (int *i = pointer; i < endpointer; i++)
								count++;
						}
						else
						{
							free(arr);
							error = 1;
						}
					}
					if (!error)
					{
						if (mysort(pointer, count, sizeof(int), &compare))
						{
							free(arr);
							if (argc == 4)
								free(newarr);
							error = 1;
						}
						else
						{
							FILE *out_file = fopen(argv[2], "w");
							if (out_file)
							{
								output(out_file, pointer, endpointer);
								fclose(out_file);
								free(arr);
								if (argc == 4)
									free(newarr);
							}
							else
							{
								free(arr);
								error = 1;
							}
						}
					}
				}
				else
				{
					free(arr);
					error = 1;
				}
			}
			else
				error = 1;
		}
		else
			error = 1;
	}
	else
		error = 1;
	return error;
}