#include <stdio.h>
#include "sort.h"
void swap(information first_elem, information second_elem)
{
	information temp;
	temp = first_elem;
	first_elem = second_elem;
	second_elem = temp;
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
				swap(stuff[i], stuff[i - 1]);
				flag = 1;
			}
	}
	while (flag);
}