#include <stdio.h>
int main()
{
	int n, div = 2;
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
			while (n > 1)
			{
				while (n % div == 0)
				{
					n /= div;
					printf(" * %d", div);
				}
				div++;
			}
			return 0;
		}
	}
	else
	{
		printf("Input error!");
		return 1;
	}
}