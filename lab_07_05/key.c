#include <stdio.h>
#include <stdlib.h>
#include "key.h"
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
			}
		}
	}
	return error;
}