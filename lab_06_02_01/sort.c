#include <stdio.h>
#include "functions.h"
void sort_stuff(information *stuff, int n)
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
}