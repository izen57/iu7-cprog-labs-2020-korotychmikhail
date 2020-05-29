#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define SUCCESS 0
#define INCORRECT_INPUT 1
#define UNKNOWN_PARAMETERS 53
#define LEN_NAME 30
#define LEN_MANUFACTURER 15
#define LEN_STRUCT 100
typedef struct
{
	char name[LEN_NAME + 2];
	char manufacturer[LEN_MANUFACTURER + 2];
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
		if (!fgets(goods[i].name, LEN_NAME + 3, file))
			return INCORRECT_INPUT;
		if (goods[i].name[LEN_NAME + 2] != '\0')
			return INCORRECT_INPUT;
		(*n)++;
		if (!fgets(goods[i].manufacturer, LEN_MANUFACTURER + 3, file))
			return INCORRECT_INPUT;
		if (goods[i].manufacturer[LEN_MANUFACTURER + 2] != '\0')
			return INCORRECT_INPUT;
		(*n)++;
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
	if (*n > LEN_STRUCT)
		return INCORRECT_INPUT;
	rewind(file);
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
	for (int i = 0; i < *n - 1; i++)
		fprintf(output_file, "%s%s%u\n%u\n", goods[i].name, goods[i].manufacturer, goods[i].cost, goods[i].amount);
	fprintf(output_file, "%s%s%u\n%u", goods[*n - 1].name, goods[*n - 1].manufacturer, goods[*n - 1].cost, goods[*n - 1].amount);
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
				printf("%s%s%u\n%u\n", goods[i].name, goods[i].manufacturer, goods[i].cost, goods[i].amount);
				break;
			}
	fclose(input_file);
	if (!count)
		return INCORRECT_INPUT;
	return SUCCESS;
}
void shift(information goods[LEN_STRUCT], int pos, int *n)
{
	(*n)++;
	for (int i = *n - 2; i >= pos; i--)
		goods[i + 1] = goods[i];
}
int add_good(char *input_output_file, information goods[LEN_STRUCT], int *n)
{
	FILE *inout_file = fopen(input_output_file, "r");
	if (!inout_file)
		return INCORRECT_INPUT;
	if (read_goods(inout_file, goods, n) && *n)
		return INCORRECT_INPUT;
	fclose(inout_file);
	inout_file = fopen(input_output_file, "w");
	information new_good;
	int count = 0;
	for (int i = 0; i <= LEN_NAME + 2; i++)
		new_good.name[i] = '\0';
	if (!fgets(new_good.name, LEN_NAME + 3, stdin))
		return INCORRECT_INPUT;
	if (new_good.name[LEN_NAME + 2] != '\0')
		return INCORRECT_INPUT;
	count++;
	for (int i = 0; i <= LEN_MANUFACTURER + 2; i++)
		new_good.manufacturer[i] = '\0';
	if (!fgets(new_good.manufacturer, LEN_MANUFACTURER + 3, stdin))
		return INCORRECT_INPUT;
	if (new_good.manufacturer[LEN_MANUFACTURER + 2] != '\0')
		return INCORRECT_INPUT;
	count++;
	if (fscanf(stdin, "%u\n", &new_good.cost) != 1)
		return INCORRECT_INPUT;
	count++;
	if (fscanf(stdin, "%u", &new_good.amount) != 1)
		return INCORRECT_INPUT;
	count++;
	if (count / 4 != 1)
		return INCORRECT_INPUT;
	int flag = 0;
	for (int i = 0; i < *n - 1; i++)
		if ((new_good.cost < goods[i].cost && new_good.cost > goods[i + 1].cost) || (new_good.cost == goods[i].cost && new_good.amount <= goods[i].amount) || (new_good.cost == goods[i + 1].cost && new_good.amount >= goods[i + 1].amount))
		{
			shift(goods, i + 1, n);
			goods[i + 1] = new_good;
			flag = 1;
			break;
		}
	if (flag)
	{
		for (int i = 0; i < *n - 1; i++)
			fprintf(inout_file, "%s%s%u\n%u\n", goods[i].name, goods[i].manufacturer, goods[i].cost, goods[i].amount);
		fprintf(inout_file, "%s%s%u\n%u", goods[*n - 1].name, goods[*n - 1].manufacturer, goods[*n - 1].cost, goods[*n - 1].amount);
		fclose(inout_file);
		return SUCCESS;
	}
	else if ((new_good.cost > goods[0].cost) || (new_good.cost == goods[0].cost && new_good.amount > goods[0].amount))
	{
		shift(goods, 0, n);
		goods[0] = new_good;
	}
	else if ((new_good.cost < goods[*n - 1].cost) || (new_good.cost == goods[*n - 1].cost && new_good.amount <= goods[*n - 1].amount))
		goods[(*n)++] = new_good;
	/*else if (new_good.cost == goods[*n - 1].cost && new_good.amount >= goods[*n - 1].amount)
	{
		shift(goods, *n - 1, n);
		goods[*n - 2] = new_good;
	}*/
	for (int i = 0; i < *n - 1; i++)
		fprintf(inout_file, "%s%s%u\n%u\n", goods[i].name, goods[i].manufacturer, goods[i].cost, goods[i].amount);
	fprintf(inout_file, "%s%s%u\n%u", goods[*n - 1].name, goods[*n - 1].manufacturer, goods[*n - 1].cost, goods[*n - 1].amount);
	fclose(inout_file);
	return SUCCESS;
}
int main(int argc, char **argv)
{
	information goods[LEN_STRUCT];
	int n = 0;
	if (!argv[1])
		return UNKNOWN_PARAMETERS;
	if (!strcmp(argv[1], "st") && argc == 4)
		return sorting_goods(argv[2], argv[3], goods, &n);
	if (!strcmp(argv[1], "ft") && argc == 4)
		return find_goods(argv[2], argv[3], goods, &n);
	if (!strcmp(argv[1], "at") && argc == 3)
		return add_good(argv[2], goods, &n);
	return UNKNOWN_PARAMETERS;
}