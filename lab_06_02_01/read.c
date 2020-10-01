#include <stdio.h>
#include <string.h>
#include "functions.h"
int read_stuff(FILE *file, information *stuff, int *n)
{
	int error = 0;
	for (int i = 0; !feof(file); i++)
	{
		if (!fgets(stuff[i].name, LEN_NAME + 2, file) || error)
			error = 1;
		if (!error && strlen(stuff[i].name) < LEN_NAME + 1)
			stuff[i].name[strcspn(stuff[i].name, "\n")] = '\0';
		if (strlen(stuff[i].name) >= LEN_NAME + 1 && !error)
			error = 1;
		if (!error)
			(*n)++;
		if (fscanf(file, "%f\n", &stuff[i].weight) != 1 || stuff[i].weight <= 0 || error)
			error = 1;
		if (!error)
			(*n)++;
		if (fscanf(file, "%f\n", &stuff[i].volume) != 1 || stuff[i].volume <= 0 || error)
			error = 1;
		if (!error)
			(*n)++;
	}
	if (*n % 3 || !*n || *n > LEN_STRUCT * 3 || error)
		error = 1;
	else
		*n /= 3;
	rewind(file);
	return error;
}