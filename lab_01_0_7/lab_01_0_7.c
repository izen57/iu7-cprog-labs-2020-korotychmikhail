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
		float f, s = 1;
		int i = 2;
		float curr = x, next = pow(x, i) / fact(i);
		do
		{
			s += curr;
			curr = next;
			next = pow(x, i + 1) / fact(i + 1);
			i++;
		} while (fabs(next - curr) > eps);
		f = exp(x);
		printf("Приближённое значение функции: %.6f\nточное значение функции: %.6f\nабсолютная ошибка прибл. значения: %.6f\nотносительная погрешность прибл. значения: %.6f", s, f, fabs(f - s), fabs((f - s) / f));
		return 0;
	}
	else
	{
		printf("Input error.");
		return 1;
	}
}