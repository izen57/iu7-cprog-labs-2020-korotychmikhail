#include <stdio.h>
#include <string.h>
#include "creat_numbers.h"
#include "print_numbers.h"
#include "sort_numbers.h"
#define SUCCESS 0
#define INCORRECT_INPUT 1
int main(int argc, char **argv)
{
	if (!strcmp(argv[1], "c") && argc == 4)
		return creat_numbers(argv[3], *argv[2] - '0');
	else if (!strcmp(argv[1], "p") && argc == 3)
		return print_numbers(argv[2]);
	else if (!strcmp(argv[1], "s") && argc == 3)
		return sort_numbers(argv[2]);
	else
		return INCORRECT_INPUT;
}