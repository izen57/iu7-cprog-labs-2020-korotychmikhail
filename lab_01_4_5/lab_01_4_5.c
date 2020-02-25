#include <stdio.h>
int mn(int n)
{
	int div = 2;
	while (n > 1)
	{
		while (n % div == 0)
		{
				n /= div;
				printf(" * %d", div);
			}
			div++;
		}
	}
int main()
{
	int n;
	if (scanf("%d", &n) == 1)
	{
		if (n <= 0)
		{
			printf("Input error!");
			return 1;
		}
		else
			if (n == 1)
			{
				return 0;
			}
		else
		{
			printf("Your integer is %d\n%d = 1", n, n);
			mn(n);
			return 0;
		}
	}
	else
	{
		printf("Input error!");
		return 1;
	}
}