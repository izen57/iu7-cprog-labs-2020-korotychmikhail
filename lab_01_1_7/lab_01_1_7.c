#include <stdio.h>
#include <math.h>
float row(float x, float eps)
{
	float s = 0, curr = x;
	float part1 = 2, part2 = 3;
	float flash = -1, num = x * x * x, denom = 1 * part1 * part2;
	float next = flash * num / denom;
	do
	{
		s += curr;
		curr = next;
		flash *= (-1);
		num *= x * x;
		part1 += 2;
		part2 += 2;
		denom *= part1 * part2;
		next = flash * num / denom;
	} while (fabs(curr) > eps);
	return s;
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
		float s = row(x, eps);
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