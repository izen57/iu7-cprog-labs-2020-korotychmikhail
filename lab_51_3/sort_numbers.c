#include <stdio.h>
#include "sort_numbers.h"
#include "file_size.h"
int get_number_by_pos(FILE *file, int pos)
{
	int num;
	fseek(file, pos, SEEK_SET);
	fread(&num, sizeof(int), 1, file);
	return num;
}
void put_number_by_pos(FILE *file, int *num, int pos)
{
	fseek(file, pos, SEEK_SET);
	fwrite(num, sizeof(int), 1, file);
}
int sort_numbers(char *path)
{
	FILE *file;
	int flag, temp, num;
	file = fopen(path, "rb+");
	if (!file)
		return INCORRECT_INPUT;
	size_t size;
	if (!file_size(file, &size))
	{
		if (size % sizeof(int))
			return INCORRECT_INPUT;
		do
		{
			flag = 0;
			for (int i = 1, byte = sizeof(int); i < size / sizeof(int); i++, byte += sizeof(int))
				if (get_number_by_pos(file, byte) < get_number_by_pos(file, byte - sizeof(int)))
				{
					temp = get_number_by_pos(file, byte);
					num = get_number_by_pos(file, byte - sizeof(int));
					put_number_by_pos(file, &num, byte);
					put_number_by_pos(file, &temp, byte - sizeof(int));
					flag = 1;
				}
		}
		while (flag);
	}
	else
		return INCORRECT_INPUT;
	return SUCCESS;
}