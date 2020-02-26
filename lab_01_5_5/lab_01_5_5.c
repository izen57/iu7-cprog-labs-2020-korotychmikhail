#include <stdio.h>

void fnc(int x)
{
	char str[255];
	int i = 0, len = 0;
	sprintf(str, "%d", x);
	while (str[i] != 0)
	{
		len++;
		i++;
	}
	for (i = 0; i < len; i++)
		printf("%c", str[i]);
}
int main()
{
	float i;
	int x;
	if (scanf("%f", &i) == 1)
	{
		int x = i;
		if (i < 0 || i - x != 0)
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