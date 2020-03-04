#include <stdio.h>

void fnc(int i)
{
	int cnt = 0, ost, x = i;
	while (i != 0)
	{
		cnt++;
		i /= 10;
	}
	int nums[cnt], j = 0;
	while (x != 0)
	{
		ost = x % 10;
		nums[j] = ost;
		j++;
		x /= 10;
	}
	for (int i = j - 1; i >= 0; i--)
		printf("%d", nums[i]);
}
int main()
{
	int i;
	if (scanf("%d", &i) == 1)
	{
		if (i <= 0)
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