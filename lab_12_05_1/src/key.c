#include <stdlib.h>
#include "../inc/key.h"
#include "../inc/error_codes.h"

int create_arr(int **begin, int count)
{
	*begin = calloc(count, sizeof(int));
	if (!*begin)
		return MEMORY_ERROR;
	else
		return SUCCESS;
}

int counting_elems(const int *begin, const int *end)
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

int *filling_array(const int *begin, const int *end, int *index)
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

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
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