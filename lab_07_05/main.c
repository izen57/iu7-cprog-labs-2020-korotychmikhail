#include <stdio.h>
#include <stdlib.h>
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
int create_arr(int **begin, int count)
{
	//printf("22\n");
	*begin = calloc(count, sizeof(int));
	if (!*begin)
	{
		//printf("23\n");
		free(begin);
		return 1;
	}
	else
	{
		//printf("24\n");
		free(begin);
		return 0;
	}
}
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
	int error = 0, count = 0;
	if (!pb_src || !pe_src || !pb_dst || !pe_dst || pb_src == pe_src)
	{
		//printf("25\n");
		free(pb_dst);
		error = 1;
	}
	if (!error)
	{
		//printf("26\n");
		int summ = 0;
		for (const int *i = pb_src; i < pe_src - 1; i++)
		{
			for (const int *j = i; j < pe_src; j++)
				summ += *j;
			if (*i > summ)
				count++;
		}
		if (!count)
		{
			//printf("27\n");
			free(pb_dst);
			error = 1;
		}
		if (!error)
		{
			if (create_arr(pb_dst, count))
			{
				//printf("28\n");
				free(pb_dst);
				error = 1;
			}
			else
			{
				//printf("29\n");
				for (const int *i = pb_src; i < pe_src - 1; i++)
					if (*i > summ)
						**pe_dst++ = *i;
			}
		}
	}
	return error;
}
int compare(const void *i, const void *j)
{
	//printf("30\n");
	const int *a = i, *b = j;
	return *a - *b;
}
int mysort(void *base, size_t num, size_t size, int compare(const void *, const void *))
{
	int error = 0;
	if (!base || !num || size != sizeof(int))
	{
		//printf("31\n");
		free(base);
		error = 1;
	}
	else
	{
		//printf("32\n");
		int *temp = NULL, *end = (int *)base + num * size, k = 0;
		for (int *i = base; i < end; i++)
		{
			for (int *j = base; j < end - *i - 1; j++)
				if (compare(i, j) < 0)
				{
					*temp = *j;
					*j = *i;
					*i = *temp;
					k = 1;
				}
			if (!k)
				break;
		}
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
				int *begin = arr, *end = arr;
				if (!read_array(in_file, &begin, &end))
				{
					//printf("4\n");
					rewind(in_file);
					int *newarr, *pointer = arr, *endnewarr = newarr, count = n;
					if (argc == 4)
					{
						//printf("5\n");
						if (!key(begin, end, &newarr, &endnewarr))
						{
							//printf("6\n");
							//*pointer = newarr;
							count = sizeof *newarr / sizeof(int);
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
						if (mysort(pointer, count, sizeof(int), compare))
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