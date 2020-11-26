#include <stdio.h>
#include <string.h>
#include "find.h"

int find_and_print_stuff(char *string, information *stuff, int n)
{
	int key = 0;
	if (!strcmp(string, "ALL"))
		key = 1;
	else
	{
		int flag = 0;
		for (int i = 0; i < n; i++)
			if (strstr(stuff[i].name, string) == stuff[i].name)
			{
				flag = 1;
				printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
			}
		if (!flag)
			key = 2;
	}
	return key;
}