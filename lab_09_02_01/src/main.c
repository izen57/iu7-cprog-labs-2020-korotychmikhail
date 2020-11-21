#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/structure.h"
#include "../inc/error_codes.h"
#include "../inc/inout.h"
#include "../inc/sort.h"
#include "../inc/find.h"
int main(int argc, char **argv)
{
	int error = 0;
	if ((argc == 2 || argc == 3) && argv[1])
	{
		FILE *file = fopen(argv[1], "r");
		if (file)
		{
			struct information *stuff;
			int n = counting_structures(file);
			if (n == -1)
			{
				fclose(file);
				error = INCORRECT_INPUT;
			}
			if (error)
				stuff = NULL;
			else
				stuff = malloc(n * sizeof(struct information));
			if (error)
			{
				fclose(file);
				error = ALLOCATION_ERROR;
			}
			if (!error && !read_stuff(file, stuff))
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
					if (!strcmp(argv[2], "ALL"))
					{
						print(stuff, n);
						free_information(stuff, n);
						fclose(file);
					}
					int m = 0;
					struct information *result = find_stuff(argv[2], stuff, n, &m);
					if (result)
					{
						print(result, m);
						free_information(stuff, n);
						free_information(result, m);
						fclose(file);
					}
					else
					{
						error = INCORRECT_INPUT;
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