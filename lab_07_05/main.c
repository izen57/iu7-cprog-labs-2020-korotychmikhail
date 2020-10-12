#include <stdio.h>
#include <stdlib.h>
int counting_numbers(FILE *file, int *n)
{
	int number, error = 0;
	for (int i = 0; !feof(file); i++)
	{
		if (fscanf(file, "%d", &number) != 1)
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
		error = 1;
	return error;
}
int create_arr(int **begin, int count)
{
	*begin = calloc(count, sizeof(int));
	if (!*begin)
		return 1;
	else
		return 0;
}
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
	int error = 0, count = 0;
	if (!pb_src || !pe_src || !pb_dst || !pe_dst || pb_src == pe_src)
		error = 1;
	if (!error)
	{
		int summ = 0;
		for (const int *i = pb_src; i < pe_src - 1; i++)
		{
			for (const int *j = i; j < pe_src; j++)
				summ += *j;
			if (*i > summ)
				count++;
		}
		if (!count)
			error = 1;
		if (!error)
		{
			if (create_arr(pb_dst, count))
			{
				free(pb_dst);
				error = 1;
			}
			else
				for (const int *i = pb_src; i < pe_src - 1; i++)
					if (*i > summ)
						**pe_dst++ = *i;
		}
	}
	return error;
}
int compare(const void *i, const void *j)
{
	const int *a = i, *b = j;
	return *a - *b;
}
void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{
	int *temp = NULL, *end = (int *)base + num * size, k = 0;
	for (int *i = base; i < end; i++)
	{
		for (int *j = base; j < end - *i - 1; j++)
			if ((*compare)(i, j) < 0)
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
void output(FILE *file, int *begin, int *end)
{
	for (int *i = begin; i < end; i++)
		fprintf(file, "%d ", *i);
}
int main(int argc, char **argv)
{
	int error = 0;
	if ((argc == 3 || argc == 4) && argv[1]/* && argv[2]*/) 
	{
		FILE *in_file = fopen(argv[1], "r");
		if (in_file)
		{
			int n = 0;
			if (!counting_numbers(in_file, &n))
			{
				rewind(in_file);
				int *arr = calloc(n, sizeof(int));
				int *begin = arr, *end = arr;
				if (!read_array(in_file, &begin, &end))
				{
					rewind(in_file);
					int *newarr = NULL, *endnewarr = newarr, count = n;
					if (argc == 4)
					{
						if (!key(begin, end, &newarr, &endnewarr))
							count = sizeof *newarr / sizeof(int);
						else
						{
							free(arr);
							error = 1;
						}
					}
					if (!error)
					{
						mysort(newarr, count, sizeof(int), &compare);
						FILE *out_file = fopen(argv[2], "w");
						if (out_file)
							output(out_file, newarr, endnewarr);
						else
							error = 1;
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