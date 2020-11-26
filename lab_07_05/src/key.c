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

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
	int error = SUCCESS;
	if (!pb_src || !pe_src || !pb_dst || !pe_dst || pb_src >= pe_src)
		error = MEMORY_ERROR;
	if (!error)
	{
		// int summ = 0;
		// for (const int *i = pb_src; i < pe_src - 1; i++)
		// {
		// 	summ = 0;
		// 	for (const int *j = i + 1; j < pe_src; j++)
		// 		summ += *j;
		// 	if (*i > summ)
		// 		count++;
		// }
		int count = counting_elems(pb_src, pe_src);
		if (!count)
			error = EMPTY_RESULT;
		if (!error)
		{
			if (create_arr(pb_dst, count))
				error = MEMORY_ERROR;
			else
			{
				int *j = *pb_dst, summ;
				for (const int *i = pb_src; i < pe_src - 1; i++)
				{
					summ = 0;
					for (const int *k = i + 1; k < pe_src; k++)
						summ += *k;
					if (*i > summ)
					{
						*j = *i;
						j++;
					}
				}
				*pe_dst = j;
			}
		}
	}
	return error;
}