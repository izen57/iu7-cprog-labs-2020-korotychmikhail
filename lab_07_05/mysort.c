//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysort.h"
int compare(const void *i, const void *j)
{
	//printf("30\n");
	const int *a = i, *b = j;
	return *a - *b;
}
int mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *))
{
	int error = 0;
	char *current_pos = (char *)base + size, *current = malloc(size), *pos;
	if (!base || !num || size != sizeof(int))
	{
		//printf("31\n");
		error = 1;
	}
	else
	{
		//printf("32\n");
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
	}
	free(current);
	return error;
}