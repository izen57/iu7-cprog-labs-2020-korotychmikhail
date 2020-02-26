#include <stdio.h>
void fnc(int x)
{
	char str[11];
	int i = 0, len = 0, temp = 0;
	sprintf(str, "%d", x);
	while (str[i] != 0)
	{
		len++;
		i++;
	}
	for (i = 0; i <= len; i++)
		printf("%c", str[i]);
}
int main()
{
	int i;
	if (scanf("%d", &i) == 1)
	{
		if (i < 0)
		{
			printf("Input error!");
			return 1;
		}
		else if (i >= 0 && i <= 9)
		{
			printf("%d", i);
			return 0;
		}
		else if (i >= 10)
		{
			fnc(i);
			return 0;
		}
	}
	else
	{
		printf("Input error!");
		return 1;
	}
}