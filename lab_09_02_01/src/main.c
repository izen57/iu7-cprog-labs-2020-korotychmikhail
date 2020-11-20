#include <stdio.h>
#include <stdlib.h>
#include "../inc/functions.h"
#include "../inc/error_codes.h"
int main(int argc, char **argv)
{
	int error = 0;
	if ((argc == 2 || argc == 3) && argv[1])
	{
		FILE *file = fopen(argv[1], "r");
		if (file)
		{
			int n = counting_structures(file);
			if (n == -1)
			{
				fclose(file);
				return INCORRECT_INPUT;
			}
			struct information *stuff = malloc(n * sizeof(struct information));
			if (!stuff)
			{
				fclose(file);
				return ALLOCATION_ERROR;
			}
			if (!read_stuff(file, stuff))
			{
				if (argc == 2)
				{
					sort_stuff(stuff, n);
					print(stuff, n);
					fclose(file);
					free_information(stuff, n);
				}
				else if (argc == 3)
				{
					error = find_and_print_stuff(argv[2], stuff, n);
					if (error == 1)
					{
						print(stuff, n);
						error = SUCCESS;
						free_information(stuff, n);
						fclose(file);
					}
					else
					{
						fclose(file);
						free_information(stuff, n);
					}
				}
			}
			else
			{
				fclose(file);
				free_information(stuff, n);
				error = ALLOCATION_ERROR;
			}
		}
		else
			error = INCORRECT_INPUT;
	}
	else
		error = INCORRECT_INPUT;
	return error;
}