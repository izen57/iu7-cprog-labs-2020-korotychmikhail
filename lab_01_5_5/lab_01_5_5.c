#include <stdio.h>

void fnc(int i)
{
	int y = 0;
	while (i)
	{
		y = y * 10 + i % 10;
		i /= 10;
	}
	while (y != 0)
	{
		int num = y % 10;
		printf("%d ", num);
		y /= 10;
	}
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
		else
			if (i >= 0 && i <= 9)
				printf("%d", i);
		else
			if (i > 9)
				fnc(i);
		return 0;
	}
	else
	{
		printf("Input error!");
		return 1;
	}
}