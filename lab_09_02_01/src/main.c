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
			struct information *stuff = NULL;
			int n = counting_structures(file);
			if (n == -1)
			{
				fclose(file);
				error = INCORRECT_INPUT;
			}
			else
			{
				stuff = malloc(n * sizeof(struct information));
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
						else
						{
							int start = 0, index = 0, flag = 0;
							while (index != -1 && start < n)
							{
								index = find_stuff(argv[2], stuff, n, start);
								if (index != -1)
								{
									flag = 1;
									printf("%s\n%f\n%f\n", stuff[index].name, stuff[index].weight, stuff[index].volume);
									start = index + 1;
								}
								else if (index == -1 && !flag)
								{
									error = INCORRECT_INPUT;
									fclose(file);
									free_information(stuff, n);
									break;
								}
							}
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
		}
		else
			error = INCORRECT_INPUT;
	}
	else
		error = INCORRECT_INPUT;
	return error;
}