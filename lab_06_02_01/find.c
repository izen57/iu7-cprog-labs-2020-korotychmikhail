#include <stdio.h>
#include <string.h>
#include "functions.h"
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