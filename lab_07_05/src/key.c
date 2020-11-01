#include <stdlib.h>
#include "../inc/key.h"
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
	if (!pb_src || !pe_src || !pb_dst || !pe_dst || pb_src >= pe_src)
		error = 1;
	if (!error)
	{
		int summ = 0;
		for (const int *i = pb_src; i < pe_src - 1; i++)
		{
			summ = 0;
			for (const int *j = i + 1; j < pe_src; j++)
				summ += *j;
			if (*i > summ)
				count++;
		}
		if (!count)
			error = 1;
		if (!error)
		{
			if (create_arr(pb_dst, count))
				error = 1;
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