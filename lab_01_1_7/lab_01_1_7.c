#include <stdio.h>
#include <math.h>
int fact(int n)
{
	int res = 1;
	for (int i = 1; i <= n; i++)
		res *= i;
	return res;
}
int main()
{
	float x, eps;
	if (scanf("%f %e", &x, &eps) == 2)
	{
		if (eps <= 0 || eps > 1)
		{
			printf("Input error.");
			return 1;
		}
		float s = 0, curr = x;
		int i = 0;
		float next = pow(-1, i + 1) * pow(x, 2 * (i + 1) + 1) / fact(2 * (i + 1) + 1);
		do
		{
			s += curr;
			curr = next;
			i++;
			next = pow(-1, i) * pow(x, 2 * i + 1) / fact(2 * i + 1);
		} while (fabs(curr) > eps);
		float f = sin(x);
		printf("%.6f %.6f %.6f %.6f", s, f, fabs(f - s), fabs((f - s) / f));
		return 0;
	}
	else
	{
		printf("Input error.");
		return 1;
	}
}