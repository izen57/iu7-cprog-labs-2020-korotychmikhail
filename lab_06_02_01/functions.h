#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#define LEN_STRUCT 15
#define LEN_NAME 25
typedef struct
{
	char name[LEN_NAME + 1];
	float weight;
	float volume;
} information;
int read_stuff(FILE *file, information *stuff, int *n);
int find_and_print_stuff(char *string, information *stuff, int n);
void sort_stuff(information *stuff, int n);
#endif