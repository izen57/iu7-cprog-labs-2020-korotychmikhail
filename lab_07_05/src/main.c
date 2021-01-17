#include <stdio.h>
#include <stdlib.h>
#include "../inc/key.h"
#include "../inc/mysort.h"
#include "../inc/inout.h"
#include "../inc/error_codes.h"

int counting(int *begin, int *end);

int main(int argc, char **argv)
{
	int error = SUCCESS;
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
					int *pointer = arr, count = n, *endpointer = end;
					if (argc == 4)
					{
						int *newarr, *endnewarr = newarr;
						if (!key(arr, end, &newarr, &endnewarr))
						{
							pointer = newarr; endpointer = endnewarr;
							count = counting(pointer, endpointer);
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
								free(pointer);
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
									free(pointer);
							}
							else
							{
								free(arr);
								error = FILE_ERROR;
							}
						}
					}
				}
				else
				{
					free(arr);
					error = READ_ERROR;
				}
			}
			else
				error = READ_ERROR;
		}
		else
			error = FILE_ERROR;
	}
	else
		error = ARGS_ERROR;
	return error;
}

int counting(int *begin, int *end)
{
	int count = 0;
	for (int *i = begin; i < end; i++)
		count++;
	return count;
}