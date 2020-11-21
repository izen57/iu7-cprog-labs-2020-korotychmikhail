#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/find.h"
#include "../inc/structure.h"
struct information *find_stuff(char *string, struct information *stuff, int n, int *m)
{
	struct information *result = NULL;
	for (int i = 0; i < n; i++)
		if (strstr(stuff[i].name, string) == stuff[i].name)
		{
			//printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
			result = realloc(result, ++(*m) * sizeof(struct information));
			result[*m - 1] = stuff[i];
		}
	return result;
}