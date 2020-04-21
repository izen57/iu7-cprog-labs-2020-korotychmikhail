#include <stdio.h>
#include <stdlib.h>
#include "my_strcspn.h"
void my_strcspn(char a[LINE_LENGHT + 1], char b[LINE_LENGHT + 1])
{
	if (a[0] == '\0' || b[0] == '\0' || a[0] == '\n' || b[0] == '\n')
		EXIT_FAILURE;
	int flag = 0;
	for (int i = 0; a[i] != '\0'; i++)
		for (int j = 0; b[j] != '\0'; j++)
			if (a[j] == b[i])
			{
				flag = 1;
				printf("%d", j);
				EXIT_SUCCESS;
			}
	if (!flag)
	{
		int count = 0;
		for (int i = 0; b[i] != '\0'; i++)
			count++;
		printf("%d", count);
	}
}