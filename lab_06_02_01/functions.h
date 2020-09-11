#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#define SUCCESS 0
#define ARGS_ERROR 1
#define INCORRECT_INPUT 2
#define LEN_STRUCT 15
#define LEN_NAME 25
typedef struct
{
	char name[LEN_NAME + 1];
	float weight;
	float volume;
} information;
int read_stuff(FILE *file, information *stuff, int *n);
int find_stuff(FILE *file, char *string, information *stuff, int n);
int sort_stuff(FILE *file, information *stuff, int n);
#endif