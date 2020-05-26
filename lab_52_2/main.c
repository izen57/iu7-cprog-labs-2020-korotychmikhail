#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define SUCCESS 0
#define INCORRECT_INPUT 1
#define UNKNOWN_PARAMETERS 53
#define LEN_NAME 30
#define LEN_MANUFACTURER 15
#define LEN_STRUCT 2
#pragma pack(push, 1)
typedef struct
{
	char name[LEN_NAME + 1];
	char manufacturer[LEN_MANUFACTURER + 1];
	uint32_t cost;
	uint32_t amount;
} information;
int read_goods(FILE *file, information goods[LEN_STRUCT], int *n)
{
	for (int i = 0; i < LEN_STRUCT; i++)
	{
		for (int j = 0; j <= LEN_NAME + 2; j++)
			goods[i].name[j] = '\0';
		for (int j = 0; j <= LEN_MANUFACTURER + 2; j++)
			goods[i].manufacturer[j] = '\0';
	}
	for (int i = 0; !feof(file); i++)
	{
		if (!fgets(goods[i].name, LEN_NAME + 2, file))
			return INCORRECT_INPUT;
		if (goods[i].name[strlen(goods[i].name) - 1] != '\n')
			return INCORRECT_INPUT;
		(*n)++;
		for (int j = 0; goods[i].name[j] != '\0'; j++)
			if (goods[i].name[j] == '\n')
				goods[i].name[j] = '\0';
		if (!fgets(goods[i].manufacturer, LEN_MANUFACTURER + 2, file))
			return INCORRECT_INPUT;
		if (goods[i].manufacturer[strlen(goods[i].manufacturer) - 1] != '\n')
			return INCORRECT_INPUT;
		(*n)++;
		for (int j = 0; goods[i].manufacturer[j] != '\0'; j++)
			if (goods[i].manufacturer[j] == '\n')
				goods[i].manufacturer[j] = '\0';
		if (fscanf(file, "%u\n", &goods[i].cost) != 1)
			return INCORRECT_INPUT;
		(*n)++;
		if (fscanf(file, "%u\n", &goods[i].amount) != 1)
			return INCORRECT_INPUT;
		(*n)++;
	}
	if (*n % 4)
		return INCORRECT_INPUT;
	*n /= 4;
	return SUCCESS;
}
int sorting_goods(char *input_path, char *output_path, information goods[LEN_STRUCT], int *n)
{
	FILE *input_file = fopen(input_path, "r");
	if (!input_file)
		return INCORRECT_INPUT;
	FILE *output_file = fopen(output_path, "w");
	if (!output_file)
		return INCORRECT_INPUT;
	if (read_goods(input_file, goods, n))
		return INCORRECT_INPUT;
	int flag;
	information temp;
	do
	{
		flag = 0;
		for (int i = 1; i < *n; i++)
		{
			if (goods[i].cost > goods[i - 1].cost)
			{
				temp = goods[i];
				goods[i] = goods[i - 1];
				goods[i - 1] = temp;
				flag = 1;
			}
			if (goods[i].cost == goods[i - 1].cost && goods[i].amount > goods[i - 1].amount)
			{
				temp = goods[i];
				goods[i] = goods[i - 1];
				goods[i - 1] = temp;
				flag = 1;
			}
		}
	}
	while (flag);
	for (int i = 0; i < *n; i++)
		fprintf(output_file, "%s %s %u %u\n", goods[i].name, goods[i].manufacturer, goods[i].cost, goods[i].amount);
	rewind(input_file);
	fclose(input_file);
	fclose(output_file);
	return SUCCESS;
}
int find_goods(char *input_path, char *substr, information goods[LEN_STRUCT], int *n)
{
	FILE *input_file = fopen(input_path, "r");
	if (!input_file)
		return INCORRECT_INPUT;
	if (read_goods(input_file, goods, n))
		return INCORRECT_INPUT;
	int count = 0;
	for (int i = 0; i < *n; i++)
		for (char *p_str = goods[i].name; *p_str != '\0'; p_str++)
			if (!memcmp(p_str, substr, sizeof(*substr)))
			{
				count++;
				printf("%s %s %u %u\n", goods[i].name, goods[i].manufacturer, goods[i].cost, goods[i].amount);
			}
	if (!count)
		return INCORRECT_INPUT;
	return SUCCESS;
}
int main(int argc, char **argv)
{
	information goods[LEN_STRUCT];
	int n = 0;
	/*if (!strcmp(argv[1], "st") && argc == 4)
		return sorting_goods(argv[2], argv[3], goods, &n);*/
	//if (!strcmp(argv[1], "ft") && argc == 4)
		return find_goods(argv[2], argv[3], goods, &n);
	/*if (!strcmp(argv[1], "at") && argc == 3)
		return add_good(argv[2]);*/
	return UNKNOWN_PARAMETERS;
}
#pragma pack(pop)