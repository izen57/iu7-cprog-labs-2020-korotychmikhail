#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#define SUCCESS 0
#define INCORRECT_INPUT 1
#define UNKNOWN_PARAMETERS 53
#define LEN_NAME 30
#define LEN_MANUFACTURER 15
#define LEN_STRUCT 100
#pragma pack(push, 1)
typedef struct
{
	char name[LEN_NAME + 1];
	char manufacturer[LEN_MANUFACTURER + 1];
	uint32_t cost;
	uint32_t amount;
} information;
int read_goods(FILE *file, information goods[LEN_STRUCT])
{
	for (int i = 0; !feof(file); i++)
	{
		fgets(goods[i].name, LEN_NAME + 2, file);
		if (goods[i].name[LEN_NAME + 1] != '\n')
			return INCORRECT_INPUT;
		for (int j = 0; j <= LEN_NAME + 2; j++)
			if (goods[i].name[j] == '\n')
				goods[i].name[j] = '\0';
		fgets(goods[i].manufacturer, LEN_MANUFACTURER + 2, file);
		if (goods[i].manufacturer[LEN_MANUFACTURER + 1] != '\n')
			return INCORRECT_INPUT;
		for (int j = 0; j <= LEN_MANUFACTURER + 2; j++)
			if (goods[i].manufacturer[j] == '\n')
				goods[i].manufacturer[j] = '\0';
		fscanf(file, "%" SCNu32, goods[i].cost);
		fscanf(file, "%" SCNu32, goods[i].amount);
	}
	return SUCCESS;
}
void sorting_goods(char *input_path, /*char *output_path,*/ information goods[LEN_STRUCT])
{
	FILE *input_file;
	input_file = fopen(input_path, "r");
	/*if (!input_file)
		return INCORRECT_INPUT;*/
	int i;
}
int main(int argc, char **argv)
{
	information goods[LEN_STRUCT];
	for (int i = 0; i < LEN_STRUCT; i++)
	{
		for (int j = 0; j < LEN_NAME; j++)
			goods[i].name[j] = '\0';
		for (int j = 0; j < LEN_MANUFACTURER; j++)
			goods[i].manufacturer[j] = '\0';
	}
	if (!strcmp(argv[1], "st") && argc == 4)
	{
		return sorting_goods(argv[2], argv[3], goods);
	}
	/*if (!strcmp(argv[1], "ft") && argc == 4)
		return find_goods(argv[2], argv[3]);
	if (!strcmp(argv[1], "at") && argc == 3)
		return add_good(argv[2]);*/
	return UNKNOWN_PARAMETERS;
}
#pragma pack(pop)