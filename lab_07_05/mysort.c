#include <stdio.h>
//#include "mysort.h"
int compare(const void *i, const void *j)
{
	//printf("30\n");
	const int *a = i, *b = j;
	return *a - *b;
}
int mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{
	int error = 0;
	if (!base || !num || size != sizeof(int))
	{
		//printf("31\n");
		error = 1;
	}
	else
	{
		//printf("32\n");
		int *end = (int *)base + num, *j = base, temp;
		for (int *i = base; i < end; i++)
		{
			temp = *i;
			for (j = i - 1; j >= (int *)base && (*compare)(j, &temp) > 0; j--)
				*(j + 1) = *j;
			*(j + 1) = temp;
		}
	}
	return error;
}