#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
	char *name;
	float weight;
	float volume;
} information;
void print(information *stuff, int n) {
	for (int i = 0; i < n; i++)
		printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
}
int input(FILE *file, information *stuff, int number)
{
	int symbol, flag = 0, n = 0;
	while ((symbol = fgetc(file)) != '\n' || symbol != EOF)
	{
		flag = 1;
		char *letter = malloc(sizeof(char));
		stuff[number].name = realloc(stuff[number].name, ++n * sizeof(char));
		strcat(stuff[number].name, itoa(symbol, letter, 10));
		free(letter);
	}
	return flag;
}
int read_stuff(FILE *file, information *stuff, int *n)
{
	int error = 0;
	for (int i = 0; !feof(file); i++)
	{
		//stuff[i].name = "";
		if (!input(file, stuff, i) || error)
			error = 1;
		/*if (!fgets(stuff[i].name, LEN_NAME + 2, file) || error)
			error = 1;*/
		/*if (!error)
			stuff[i].name[strcspn(stuff[i].name, "\n")] = '\0';*/
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
		if (!error)
		{
			stuff = realloc(stuff, *n * sizeof(information) / 3);
			if (!stuff)
				error = 1;
		}
	}
	if (*n % 3 || !*n || error)
		error = 1;
	else
		*n /= 3;
	rewind(file);
	return error;
}
int main(/*int argc, char **argv*/) {
	int error = 0;
	//if ((argc == 2 || argc == 3) && argv[1]) {
		FILE *file = fopen(/*argv[1]*/"D:\\C\\iu7-cprog-labs-2020-korotychmikhail\\lab_09_02_01\\in.txt", "r");
		if (file) {
			int n = 0;
			information *stuff = malloc(sizeof(information));
			stuff->name = malloc(sizeof(char *));
			if (!read_stuff(file, stuff, &n)) {
				print(stuff, n);
				free(stuff);
				fclose(file);
			}
			else
				error = 1;
		}
		else
			error = 1;
	//}
	//else
	//	error = 1;
	return error;
}