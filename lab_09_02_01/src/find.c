#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/find.h"
#include "../inc/structure.h"
#include "../inc/inout.h"

int find_stuff(char *string, struct information *stuff, int n, int start)
{
	int index = -1;
	for (int i = start; i < n; i++)
		if (strstr(stuff[i].name, string) == stuff[i].name)
		{
			index = i;
			break;
		}
	return index;
}