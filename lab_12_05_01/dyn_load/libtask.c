#include "libtask.h"

ARR_DLL int ARR_DECL create_arr(int **begin, int count)
{
	*begin = calloc(count, sizeof(int));
	if (!*begin)
		return MEMORY_ERROR;
	else
		return SUCCESS;
}

ARR_DLL int ARR_DECL counting_elems(const int *begin, const int *end)
{
	int summ = 0, count = 0;
	for (const int *i = begin; i < end - 1; i++)
	{
		summ = 0;
		for (const int *j = i + 1; j < end; j++)
			summ += *j;
		if (*i > summ)
			count++;
	}
	return count;
}

ARR_DLL int *ARR_DECL filling_array(const int *begin, const int *end, int *index)
{
	for (const int *i = begin; i < end - 1; i++)
	{
		int summ = 0;
		for (const int *k = i + 1; k < end; k++)
			summ += *k;
		if (*i > summ)
			*index++ = *i;
	}
	return index;
}

ARR_DLL int ARR_DECL key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
	int error = SUCCESS;
	if (!pb_src || !pe_src || !pb_dst || !pe_dst || pb_src >= pe_src)
		error = MEMORY_ERROR;
	if (!error)
	{
		int *j = *pb_dst;
		*pe_dst = filling_array(pb_src, pe_src, j);
	}
	return error;
}

ARR_DLL int ARR_DECL counting_numbers(FILE *file, int *n)
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

ARR_DLL int ARR_DECL read_array(FILE *file, int **begin, int **end)
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

ARR_DLL void ARR_DECL output(FILE *file, int *begin, int *end)
{
	for (int *i = begin; i < end; i++)
		fprintf(file, "%d ", *i);
}

ARR_DLL int ARR_DECL compare(const void *i, const void *j)
{
	const int *a = i, *b = j;
	return *a - *b;
}

ARR_DLL int ARR_DECL mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{
	int error = SUCCESS;
	char *current_pos = (char *) base + size, *current = malloc(size), *pos;
	if (!base || num < 1)
		error = EMPTY_RESULT;
	else
		for (size_t i = 1; i < num; ++i)
		{
			pos = current_pos;
			memcpy(current, current_pos, size);
			for (int j = i; j > 0 && compare(pos - size, current) > 0; --j)
			{
				memcpy(pos, pos - size, size);
				pos -= size;
			}
			memcpy(pos, current, size);
			current_pos += size;
		}
	free(current);
	return error;
}

ARR_DLL int ARR_DECL counting(int *begin, int *end)
{
	int count = 0;
	for (int *i = begin; i < end; i++)
		count++;
	return count;
}