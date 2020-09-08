#include <stdio.h>
#include <string.h>
#define SUCCESS 0
#define ARGS_ERROR 1
#define INCORRECT_INPUT 2
#define LEN_STRUCT 15
#define LEN_NAME 25
typedef struct
{
	char name[LEN_NAME + 1];
	float weight;
	float volume;
} information;
int read_stuff(FILE *file, information *stuff, int *n)
{
	for (int i = 0; i < LEN_STRUCT; i++)
		for (int j = 0; j < LEN_NAME + 2; j++)
			stuff[i].name[j] = '\0';
	for (int i = 0; !feof(file); i++)
	{
		if (!fgets(stuff[i].name, LEN_NAME + 1, file))
			return INCORRECT_INPUT;
		for (int j = 0; j < strlen(stuff[i].name); j++)
			if (stuff[i].name[j] == '\n')
				stuff[i].name[j] = '\0';
		(*n)++;
		if (fscanf(file, "%f\n", &stuff[i].weight) != 1)
			return INCORRECT_INPUT;
		(*n)++;
		if (fscanf(file, "%f\n", &stuff[i].volume) != 1)
			return INCORRECT_INPUT;
		(*n)++;
	}
	if (*n % 3)
		return INCORRECT_INPUT;
	else
		*n /= 3;
	if (!*n)
		return INCORRECT_INPUT;
	rewind(file);
	return SUCCESS;
}
int find_stuff(FILE *file, char *string, information *stuff, int n)
{
	if (!strcmp(string, "ALL"))
		for (int i = 0; i < n; i++)
			printf("%s\n%.6f\n%.6f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
	else
		for (int i = 0; i < n; i++)
			if (!memcmp(stuff[i].name, string, sizeof(*string)))
				printf("%s\n%.6f\n%.6f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
	fclose(file);
	return SUCCESS;
}
int sort_stuff(FILE *file, information *stuff, int n)
{
	int flag;
	information temp;
	do
	{
		flag = 0;
		for (int i = 1; i < n; i++)
			if (stuff[i].weight / stuff[i].volume < stuff[i - 1].weight / stuff[i - 1].volume)
			{
				temp = stuff[i];
				stuff[i] = stuff[i - 1];
				stuff[i - 1] = temp;
				flag = 1;
			}
	}
	while (flag);
	for (int i = 0; i < n; i++)
		printf("%s\n%.6f\n%.6f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
	fclose(file);
	return SUCCESS;
}
int main(int argc, char **argv)
{
	if ((argc != 2 && argc != 3) || !argv[1])
	{
		//printf("1\n");
		return ARGS_ERROR;
	}
	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		//printf("2\n");
		return INCORRECT_INPUT;
	}
	information stuff[LEN_STRUCT];
	int n = 0;
	if (read_stuff(file, stuff, &n))
	{
		//printf("3\n");
		return INCORRECT_INPUT;
	}
	if (argc == 2)
	{
		//printf("4\n");
		return sort_stuff(file, stuff, n);
	}
	if (argc == 3)
	{
		//printf("5\n");
		return find_stuff(file, argv[2], stuff, n);
	}
}