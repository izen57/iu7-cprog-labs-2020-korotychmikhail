#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "functions.h"
int main(int argc, char **argv)
{
	information goods[LEN_STRUCT];
	int n = 0;
	if (!argv[1])
		return UNKNOWN_PARAMETERS;
	if (!strcmp(argv[1], "st") && argc == 4)
		return sorting_goods(argv[2], argv[3], goods, &n);
	if (!strcmp(argv[1], "ft") && argc == 4)
		return find_goods(argv[2], argv[3], goods, &n);
	if (!strcmp(argv[1], "at") && argc == 3)
		return add_good(argv[2], goods, &n);
	return UNKNOWN_PARAMETERS;
}