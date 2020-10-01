#include <stdio.h>
#include <string.h>
#include "functions.h"
int read_stuff(FILE *file, information *stuff, int *n)
{
	int error = 0;
	for (int i = 0; !feof(file); i++)
	{
		if (error || !fgets(stuff[i].name, LEN_NAME + 2, file))
			error = 1;
		if (!error)
			stuff[i].name[strcspn(stuff[i].name, "\n")] = '\0';
		if (!error || strlen(stuff[i].name) >= LEN_NAME)
			error = 1;
		if (!error)
			(*n)++;
		if (error || fscanf(file, "%f\n", &stuff[i].weight) != 1 || stuff[i].weight <= 0)
			error = 1;
		if (!error)
			(*n)++;
		if (error || fscanf(file, "%f\n", &stuff[i].volume) != 1 || stuff[i].volume <= 0)
			error = 1;
		if (!error)
			(*n)++;
	}
	if (error || *n % 3 || !*n || *n > LEN_STRUCT * 3)
		error = 1;
	else
	{
		*n /= 3;
		rewind(file);
	}
	return error;
}