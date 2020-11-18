#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
	char *name;
	float weight;
	float volume;
} information;
void print(information *stuff, int n)
{
	for (int i = 0; i < n; i++)
		printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
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
int read_stuff(FILE *file, information *stuff)
{
	int error = 0;
	for (int i = 0; !feof(file); i++)
	{
		if (!error)
			stuff[i].name = input(file);
		if (error || !stuff[i].name)
			error = 1;
		printf("%s\n", stuff[i].name);
		if (error || fscanf(file, "%f\n", &stuff[i].weight) != 1 || stuff[i].weight <= 0)
			error = 1;
		if (error || fscanf(file, "%f\n", &stuff[i].volume) != 1 || stuff[i].volume <= 0)
			error = 1;
	}
	rewind(file);
	return error;
}
void free_information(information *stuff, int n)
{
	for (int i = 0; i < n; i++)
		free(stuff[i].name);
}
int main(void) {
	int error = 0;
	//if ((argc == 2 || argc == 3) && argv[1]) {
		FILE *file = fopen("D:\\c\\iu7-cprog-labs-2020-korotychmikhail\\lab_09_02_01\\in.txt", "r");
		if (file)
		{
			int n = counting_structures(file);
			if (n == -1)
				return 1;
			information *stuff = malloc(n * sizeof(information));
			if (!read_stuff(file, stuff))
			{
				print(stuff, n);
				free_information(stuff, n);
				free(stuff);
				fclose(file);
			}
			else
			{
				error = 1;
				free_information(stuff, n);
				free(stuff);
				fclose(file);
			}
		}
		else
			error = 1;
	//}
	//else
	//	error = 1;
	return error;
}