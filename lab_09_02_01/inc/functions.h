#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
typedef struct
{
	char *name;
	float weight;
	float volume;
} information;
int read_stuff(FILE *file, information *stuff, int *n);
int find_and_print_stuff(char *string, information *stuff, int n);
void sort_stuff(information *stuff, int n);
#endif