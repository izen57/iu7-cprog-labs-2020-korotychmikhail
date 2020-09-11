#include <stdio.h>
#include <string.h>
#include "functions.h"
int read_stuff(FILE *file, information *stuff, int *n)
{
	for (int i = 0; !feof(file); i++)
	{
		if (!fgets(stuff[i].name, LEN_NAME + 2, file))
			return INCORRECT_INPUT;
		stuff[i].name[strcspn(stuff[i].name, "\n")] = '\0';
		if (strlen(stuff[i].name) >= LEN_NAME + 1)
			return 1;
		(*n)++;
		if (fscanf(file, "%f\n", &stuff[i].weight) != 1 || stuff[i].weight <= 0)
			return INCORRECT_INPUT;
		(*n)++;
		if (fscanf(file, "%f\n", &stuff[i].volume) != 1 || stuff[i].volume <= 0)
			return INCORRECT_INPUT;
		(*n)++;
	}
	if (*n % 3 || !*n || *n > LEN_STRUCT * 3)
		return INCORRECT_INPUT;
	else
		*n /= 3;
	rewind(file);
	return SUCCESS;
}
int find_stuff(FILE *file, char *string, information *stuff, int n)
{
	if (!strcmp(string, "ALL"))
		for (int i = 0; i < n; i++)
			printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
	else
	{
		int flag = 0;
		for (int i = 0; i < n; i++)
			if (strstr(stuff[i].name, string) == stuff[i].name)
			{
				flag = 1;
				printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
			}
		if (!flag)
			return INCORRECT_INPUT;
	}
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
		printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
	fclose(file);
	return SUCCESS;
}