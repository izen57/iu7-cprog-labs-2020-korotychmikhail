#define __POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/functions.h"
int read_stuff(FILE *file, information *stuff, int *n)
{
	int error = 0;
	for (int i = 0; !feof(file); i++)
	{
		stuff[i].name = NULL;
		size_t len = 0;
		if (getline(stuff[i].name, &len, file) == -1 || error)
			error = 1;
		/*if (!fgets(stuff[i].name, LEN_NAME + 2, file) || error)
			error = 1;*/
		if (!error)
			stuff[i].name[strcspn(stuff[i].name, "\n")] = '\0';
		//if ((strlen(stuff[i].name) >= LEN_NAME + 1 || !strlen(stuff[i].name)) && !error)
			//error = 1;
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
		stuff = realloc(stuff, *n * sizeof(information) / 3);
		if (!stuff)
			error = 1;
	}
	if (*n % 3 || !*n || error)
		error = 1;
	else
		*n /= 3;
	rewind(file);
	return error;
}