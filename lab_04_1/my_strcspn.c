#include <string.h>
#include "my_strcspn.h"
int my_strcspn(char *a, char *b)
{
	int res;
	if (a[0] == '\0' || b[0] == '\n')
		res = 0;
	int flag = 0;
	for (int i = 0; i < strlen(a) + 2; i++)
		for (int j = 0; j < strlen(b) + 2; j++)
			if (a[i] == b[j])
			{
				flag = 1;
				res = i;
				break;
			}
	if (!flag)
		res = strlen(a);
	return res;
}