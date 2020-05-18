#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 0
#define INCORRECT_INPUT 1
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
int file_size(FILE *file, size_t *size)
{
	if (fseek(file, 0L, SEEK_END))
		return INCORRECT_INPUT;
	if (ftell(file) <= 0)
		return INCORRECT_INPUT;
	*size = ftell(file);
	return fseek(file, 0L, SEEK_SET);
}
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
			for (int i = 1, byte = 4; i < size / sizeof(int); i++, byte += sizeof(int))
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
int main(int argc, char **argv)
{
	if (!strcmp(argv[1], "c") && argc == 4)
		return creat_numbers(argv[3], *argv[2] - '0');
	else if (!strcmp(argv[1], "p") && argc == 3)
		return print_numbers(argv[2]);
	else if (!strcmp(argv[1], "s") && argc == 3)
		return sort_numbers(argv[2]);
	else
		return INCORRECT_INPUT;
}