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
		float f, s = 0;
		int i = 1;
		float curr = x;
		float next = pow(-1, i + 1) * pow(x, 2 * i + 2) / fact(2 * i + 2);
		do
		{
			s += curr;
			curr = next;
			next = pow(-1, i + 2) * pow(x, 2 * i + 3) / fact(2 * i + 3);
			i++;
		} while (fabs(curr) > eps);
		f = sin(x);
		printf("%.6f %.6f %.6f %.6f", s, f, fabs(f - s), fabs((f - s) / f));
		return 0;
	}
	else if (eps < 0 || eps > 1)
	{
		printf("Input error.");
		return 1;
	}
}