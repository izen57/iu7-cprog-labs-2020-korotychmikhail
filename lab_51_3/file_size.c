#include <stdio.h>
#include "file_size.h"
int file_size(FILE *file, size_t *size)
{
	if (fseek(file, 0L, SEEK_END))
		return INCORRECT_INPUT;
	if (ftell(file) <= 0)
		return INCORRECT_INPUT;
	*size = ftell(file);
	return fseek(file, 0L, SEEK_SET);
}