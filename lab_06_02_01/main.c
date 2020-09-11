#include <stdio.h>
#include "functions.h"
int main(int argc, char **argv)
{
	if ((argc != 2 && argc != 3) || !argv[1])
		return ARGS_ERROR;
	FILE *file = fopen(argv[1], "r");
	if (!file)
		return INCORRECT_INPUT;
	information stuff[LEN_STRUCT];
	int n = 0;
	if (read_stuff(file, stuff, &n))
		return INCORRECT_INPUT;
	if (argc == 2)
		return sort_stuff(file, stuff, n);
	if (argc == 3)
		return find_stuff(file, argv[2], stuff, n);
}