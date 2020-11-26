#include <stdio.h>
#include "../inc/sort.h"
#include "../inc/structure.h"

void swap(struct information *elem1, struct information *elem2)
{
	struct information temp;
	temp = *elem1;
	*elem1 = *elem2;
	*elem2 = temp;
	/*temp = stuff[index1];
	stuff[index1] = stuff[index2];
	stuff[index2] = temp;*/
}

void sort_stuff(struct information *stuff, int n)
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