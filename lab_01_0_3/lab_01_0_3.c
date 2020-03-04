#include <stdio.h>

int main()
{
	float h, t, m;
	scanf("%f %f %f", &h, &t, &m);
	weight = h * t / 240;
	index = m / ((h / 100) * (h / 100));
	printf("%.5f %.5f", weight, index);
	return 0;
}