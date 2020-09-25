#include <stdio.h>
#include "functions.h"
int main(int argc, char **argv)
{
	int error = 0;
	if ((argc == 2 || argc == 3) && argv[1])
	{
		FILE *file = fopen(argv[1], "r");
		if (file)
		{
			information stuff[LEN_STRUCT];
			int n = 0;
			if (!read_stuff(file, stuff, &n))
			{
				if (argc == 2)
				{
					sort_stuff(stuff, n);
					fclose(file);
				}
				else if (argc == 3)
				{
					error = find_and_print_stuff(argv[2], stuff, n);
					if (error == 1)
					{
						for (int i = 0; i < n; i++)
							printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
						error = 0;
					}
					fclose(file);
				}
			}
			else
				error = 1;
		}
		else
			error = 1;
	}
	else
		error = 1;
	return error;
}