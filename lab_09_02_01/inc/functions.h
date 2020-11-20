#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
struct information
{
	char *name;
	float weight;
	float volume;
};
void print(struct information *stuff, int n);
void free_information(struct information *stuff, int n);
char *input(FILE *file);
int counting_structures(FILE *file);
int read_stuff(FILE *file, struct information *stuff);
int find_and_print_stuff(char *string, struct information *stuff, int n);
void sort_stuff(struct information *stuff, int n);
#endif