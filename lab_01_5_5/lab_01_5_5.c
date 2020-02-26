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
		printf("%d", str[i] - '0');
}
int main()
{
	float i;
	if (scanf("%f", &i) == 1)
	{
		int x = i;
		if (x < 0 || i - x != 0)
		{
			printf("Input error!");
			return 1;
		}
		else if (x >= 0 && x <= 9)
		{
			printf("%d", x);
			return 0;
		}
		else if (x >= 10)
		{
			fnc(x);
			return 0;
		}
	}
	else
	{
		printf("Input error!");
		return 1;
	}
}