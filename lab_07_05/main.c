#include <stdio.h>
#include <stdlib.h>
#include "mysort.h"
#include "key.h"
int counting_numbers(FILE *file, int *n)
{
	//printf("18\n");
	int number, error = 0;
	for (int i = 0; !feof(file); i++)
	{
		if (fscanf(file, "%d", &number) == 1)
			(*n)++;
		else
		{
			//printf("19\n");
			error = 1;
			break;
		}
	}
	return error;
}
int read_array(FILE *file, int **begin, int **end)
{
	//printf("20\n");
	int error = 0;
	while (!feof(file))
	{
		fscanf(file, "%d", *end);
		(*end)++;
	}
	if (*begin == *end)
	{
		//printf("21\n");
		free(begin);
		error = 1;
	}
	return error;
}
void output(FILE *file, int *begin, int *end)
{
	//printf("33\n");
	for (int *i = begin; i < end; i++)
		fprintf(file, "%d ", *i);
}
int main(int argc, char **argv)
{
	//printf("0\n");
	int error = 0;
	if ((argc == 3 || argc == 4) && argv[1] && argv[2])
	{
		//printf("1\n");
		FILE *in_file = fopen(argv[1], "r");
		if (in_file)
		{
			//printf("2\n");
			int n = 0;
			if (!counting_numbers(in_file, &n))
			{
				//printf("3\n");
				rewind(in_file);
				int *arr = calloc(n, sizeof(int));
				int *end = arr;
				if (!read_array(in_file, &arr, &end))
				{
					//printf("4\n");
					rewind(in_file);
					int *newarr, *pointer = arr, count = n, *endpointer = end, *endnewarr = newarr + count;
					if (argc == 4)
					{
						//printf("5\n");
						if (!key(arr, end, &newarr, &endnewarr))
						{
							//printf("6\n");
							pointer = newarr;
							endpointer = endpointer;
							count = 0;
							for (int *i = newarr; i < endnewarr; ++i)
								count++;
						}
						else
						{
							//printf("7\n");
							free(arr);
							error = 1;
						}
					}
					if (!error)
					{
						//printf("8\n");
						if (mysort(pointer, count, sizeof(int), &compare))
						{
							//printf("9\n");
							error = 1;
						}
						else
						{
							//printf("10\n");
							FILE *out_file = fopen(argv[2], "w");
							if (out_file)
							{
								//printf("11\n");
								output(out_file, newarr, endnewarr);
							}
							else
							{
								//printf("12\n");
								error = 1;
							}
						}
					}
				}
				else
				{
					//printf("13\n");
					free(arr);
					error = 1;
				}
			}
			else
			{
				//printf("14\n");
				error = 1;
			}
		}
		else
		{
			//printf("15\n");
			error = 1;
		}
	}
	else
	{
		//printf("16\n");
		error = 1;
	}
	//printf("17\n");
	return error;
}