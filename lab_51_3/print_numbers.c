#include <stdio.h>
#include "print_numbers.h"
#include "file_size.h"
int print_numbers(char *path)
{
	FILE *file;
	file = fopen(path, "rb");
	if (!file)
		return INCORRECT_INPUT;
	int val;
	size_t size;
	if (!file_size(file, &size))
	{
		if (size % sizeof(int))
			return INCORRECT_INPUT;
		for (int i = 0; i < size / sizeof(int); i++)
		{
			if (fread(&val, sizeof(int), 1, file) == 1)
				printf("%d ", val);
			else
				break;
		}
	}
	else
		return INCORRECT_INPUT;
	return SUCCESS;
}