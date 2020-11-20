#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/functions.h"
#include "../inc/error_codes.h"
void print(struct information *stuff, int n)
{
	for (int i = 0; i < n; i++)
		printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
}
void free_information(struct information *stuff, int n)
{
	for (int i = 0; i < n; i++)
		free(stuff[i].name);
	free(stuff);
}
char *input(FILE *file)
{
	int capacity = 1, size = 0;
	char *s = (char *)malloc(capacity * sizeof(char));
	for (char c = fgetc(file); c != '\n' && c != EOF; c = fgetc(file))
	{
		s[size++] = c;
		if (size >= capacity)
		{
			capacity *= 2;
			s = (char *)realloc(s, capacity * sizeof(char));
			if (!s)
				return NULL;
		}
	}
	s[size] = '\0';
	return s;
}
int counting_structures(FILE *file)
{
	int n = 0;
	while (!feof(file))
		if (fgetc(file) == '\n')
			n++;
	n++;
	rewind(file);
	if (n % 3)
		return -1;
	else
		return n / 3;
}
int read_stuff(FILE *file, struct information *stuff)
{
	int error = 0;
	for (int i = 0; !feof(file); i++)
	{
		if (!error)
			stuff[i].name = input(file);
		if (error || !stuff[i].name)
			error = INCORRECT_INPUT;
		printf("%s\n", stuff[i].name);
		if (error || fscanf(file, "%f\n", &stuff[i].weight) != 1 || stuff[i].weight <= 0)
			error = INCORRECT_INPUT;
		if (error || fscanf(file, "%f\n", &stuff[i].volume) != 1 || stuff[i].volume <= 0)
			error = INCORRECT_INPUT;
	}
	rewind(file);
	return error;
}