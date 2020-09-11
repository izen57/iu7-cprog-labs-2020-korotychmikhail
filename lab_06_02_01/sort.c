#include <stdio.h>
#include <string.h>
#include "functions.h"
int sort_stuff(FILE *file, information *stuff, int n)
{
	int flag;
	information temp;
	do
	{
		flag = 0;
		for (int i = 1; i < n; i++)
			if (stuff[i].weight / stuff[i].volume < stuff[i - 1].weight / stuff[i - 1].volume)
			{
				temp = stuff[i];
				stuff[i] = stuff[i - 1];
				stuff[i - 1] = temp;
				flag = 1;
			}
	}
	while (flag);
	for (int i = 0; i < n; i++)
		printf("%s\n%f\n%f\n", stuff[i].name, stuff[i].weight, stuff[i].volume);
	fclose(file);
	return SUCCESS;
}