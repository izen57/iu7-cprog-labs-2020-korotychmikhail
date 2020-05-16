#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 0
#define INCORRECT_INPUT -1
int creat_numbers(char *path, int number)
{
	FILE *file;
	file = fopen(path, "wb");
	for (int i = 0; i < number; i++)
	{
		int val = rand() % (number * 2);
		if (fwrite(&val, sizeof(int), 1, file) != 1)
			return INCORRECT_INPUT;
	}
	fclose(file);
	return SUCCESS;
}
int file_size(FILE *file, size_t *size)
{
	if (fseek(file, 0, SEEK_END))
		return INCORRECT_INPUT;
	if (ftell(file) < 0)
		return INCORRECT_INPUT;
	*size = ftell(file);
	return fseek(file, 0, SEEK_SET);
}
int print_numbers(char *path, size_t *size)
{
	FILE *file;
	file = fopen(path, "rb");
	int val;
	if (!file_size(file, size))
		for (size_t i = 0; i < *size / sizeof(int); i++)
		{
			if (fread(&val, sizeof(int), 1, file))
				printf("%d ", val);
			else
				break;
		}
	else
		return INCORRECT_INPUT;
	fclose(file);
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
int sort_numbers(char *path, size_t *size)
{
	FILE *file;
	int flag, temp, num;
	file = fopen(path, "rb+");
	if (!file_size(file, size))
		do
		{
			flag = 0;
			for (size_t i = 1; i < *size / sizeof(int); i++)
				if (get_number_by_pos(file, i) < get_number_by_pos(file, i - 1))
				{
					temp = get_number_by_pos(file, i);
					num = get_number_by_pos(file, i - 1);
					put_number_by_pos(file, &num, i);
					put_number_by_pos(file, &temp, i - 1);
					flag = 1;
				}
		}
		while (flag);
	else
	{
		printf("!file_size");
		return INCORRECT_INPUT;
	}
	return SUCCESS;
}
int main(int argc, char **argv)
{
	if (!strcmp(argv[1], "c"))
		return creat_numbers(argv[3], *argv[2] - '0');
	size_t size;
	if (!strcmp(argv[1], "p"))
		return print_numbers(argv[2], &size);
	if (!strcmp(argv[1], "s"))
		return sort_numbers(argv[2], &size);
}