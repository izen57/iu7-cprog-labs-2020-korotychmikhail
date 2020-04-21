#include <stdio.h>
#include <string.h>
#include "my_strcspn.h"
status_code my_strcspn(char a[LINE_LENGHT + 1], char b[LINE_LENGHT + 1])
{
	if (a[0] == '\0' || b[0] == 0)
		return incorrect_input;
	int flag = 0;
	for (int i = 0; a[i] != '\0'; i++)
		for (int j = 0; b[j] != '\0'; j++)
			if (a[i] == b[j])
			{
				flag = 1;
				printf("%d", i);
				return success;
			}
	if (!flag)
	{
		printf("%ld", strlen(a));
		return success;
	}
}