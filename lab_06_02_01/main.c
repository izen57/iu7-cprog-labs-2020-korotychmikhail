#include <stdio.h>
#include "functions.h"
int main(int argc, char **argv)
{
	int error = 0;
	if ((argc == 2 || argc == 3) && argv[1])
	{
		//printf("8");
		FILE *file = fopen(argv[1], "r");
		if (file)
		{
			//printf("12");
			information stuff[LEN_STRUCT];
			int n = 0;
			if (!read_stuff(file, stuff, &n))
			{
				//printf("17");
				if (argc == 2)
				{
					//printf("20");
					sort_stuff(stuff, n);
					for (int i = 0; i < n; i++)
						printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
					fclose(file);
				}
				else if (argc == 3)
				{
					//printf("26");
					error = find_and_print_stuff(argv[2], stuff, n);
					if (error == 1)
					{
						//printf("30");
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