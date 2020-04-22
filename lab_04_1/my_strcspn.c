#include <stdio.h>
#include "my_strcspn.h"
int my_strcspn(char *a, char *b)
{
	int count = 0;
	if (a[0] == '\0' || b[0] == '\0' || a[0] == '\n' || b[0] == '\n')
		return count;
	int flag = 0;
	for (int i = 0; a[i] != '\0'; i++)
		for (int j = 0; b[j] != '\0'; j++)
			if (a[i] == b[j])
			{
				flag = 1;
				count = i;
				return count;
			}
	if (!flag)
	{
		count = 0;
		for (int i = 0; a[i] != '\0'; i++)
			count++;
		return count;
	}
}