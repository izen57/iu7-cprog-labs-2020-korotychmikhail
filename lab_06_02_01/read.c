#include <stdio.h>
#include <string.h>
#include "functions.h"
int read_stuff(FILE *file, information *stuff, int *n)
{
	int flag = 0;
	for (int i = 0; !feof(file); i++)
	{
		if (!fgets(stuff[i].name, LEN_NAME + 2, file))
			flag = 1;
		stuff[i].name[strcspn(stuff[i].name, "\n")] = '\0';
		if (strlen(stuff[i].name) >= LEN_NAME + 1)
			flag = 1;
		(*n)++;
		if (fscanf(file, "%f\n", &stuff[i].weight) != 1 || stuff[i].weight <= 0)
			flag = 1;
		(*n)++;
		if (fscanf(file, "%f\n", &stuff[i].volume) != 1 || stuff[i].volume <= 0)
			flag = 1;
		(*n)++;
	}
	if (*n % 3 || !*n || *n > LEN_STRUCT * 3)
		flag = 1;
	else
		*n /= 3;
	rewind(file);
	return flag;
}