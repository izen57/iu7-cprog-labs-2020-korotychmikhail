#include <stdio.h>
#include "my_strcspn.h"
void my_strcspn(char a[LINE_LENGHT + 1], char b[LINE_LENGHT + 1], int n, int m)
{
	int flag = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (a[i] == b[j])
			{
				flag = 1;
				printf("%d", i);
				break;
			}
	if (!flag)
		printf("%d", LINE_LENGHT);
}