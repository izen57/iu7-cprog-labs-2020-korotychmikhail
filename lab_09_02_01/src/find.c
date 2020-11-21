#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/find.h"
#include "../inc/structure.h"
#include "../inc/inout.h"
int find_stuff(char *string, struct information *stuff, int n, int start)
{
	//struct information *result = NULL;
	int index = -1;
	for (int i = start; i < n; i++)
		if (strstr(stuff[i].name, string) == stuff[i].name)
		{
			index = i;
			break;
			//printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
			/*flag = 1;
			index = i;
			break;*/
			/*result = realloc(result, ++(*m) * sizeof(struct information));
			if (!result)
			{
				free_information(result, *m - 1);
				result = NULL;
				break;
			}
			char *temp = stuff[i].name;
			result[*m - 1].name = temp;
			result[*m - 1].weight = stuff[i].weight;
			result[*m - 1].volume = stuff[i].volume;*/
		}
	return index;
}