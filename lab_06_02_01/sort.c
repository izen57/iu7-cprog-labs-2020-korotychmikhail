#include <stdio.h>
#include "sort.h"

void swap(information *elem1, information *elem2)
{
	information temp;
	temp = *elem1;
	*elem1 = *elem2;
	*elem2 = temp;
}

void sort_stuff(information *stuff, int n)
{
	int flag;
	do
	{
		flag = 0;
		for (int i = 1; i < n; i++)
			if (stuff[i].weight / stuff[i].volume < stuff[i - 1].weight / stuff[i - 1].volume)
			{
				swap(&stuff[i], &stuff[i - 1]);
				flag = 1;
			}
	}
	while (flag);
}