#include <stdio.h>
#include <stdlib.h>
#include "creat_numbers.h"
int creat_numbers(char *path, int number)
{
	if (number < 1)
		return INCORRECT_INPUT;
	FILE *file;
	file = fopen(path, "wb");
	if (!file)
		return INCORRECT_INPUT;
	for (int i = 0; i < number; i++)
	{
		int val = rand() % (number * 2);
		if (fwrite(&val, sizeof(int), 1, file) != 1)
			return INCORRECT_INPUT;
	}
	return SUCCESS;
}