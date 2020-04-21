#include <stdio.h>
#include <string.h>
#include "my_strcspn.h"
void my_strcspn(char a[LINE_LENGHT + 1], char b[LINE_LENGHT + 1])
{
	int flag = 0;
	for (int i = 0; a[i] != '\0'; i++)
		for (int j = 0; b[j] != '\0'; j++)
			if (a[i] == b[j])
			{
				flag = 1;
				printf("%d", i);
			}
	if (!flag)
		printf("%ld", strlen(a));
}