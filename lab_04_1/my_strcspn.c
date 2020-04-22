#include <string.h>
#include "my_strcspn.h"
int my_strcspn(char *a, char *b)
{
	int res = 0;
	for (int i = 0; i < strlen(a) + 1; i++)
		for (int j = 0; j < strlen(b) + 1; j++)
			if (a[i] == b[j])
			{
				res = i;
				break;
			}
	return res;
}