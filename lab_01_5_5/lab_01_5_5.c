#include <stdio.h>

int fnc(int i)
{
	while (i != 0)
	{
		int num = i % 10;
		printf("%d", num);
		i /= 10;
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