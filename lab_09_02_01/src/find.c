#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/find.h"
#include "../inc/structure.h"
#include "../inc/inout.h"
struct information *find_stuff(char *string, struct information *stuff, int n, int *m)
{
	struct information *result = NULL;
	for (int i = 0; i < n; i++)
		if (strstr(stuff[i].name, string) == stuff[i].name)
		{
			//printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
			result = realloc(result, ++(*m) * sizeof(struct information));
			if (!result)
			{
				free_information(result, *m - 1);
				result = NULL;
				break;
			}
			//result[*m - 1] = stuff[i];
			result[*m - 1].name = stuff[i].name;
			result[*m - 1].weight = stuff[i].weight;
			result[*m - 1].volume = stuff[i].volume;
		}
	return result;
}