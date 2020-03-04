#include <stdio.h>

int main()
{
	float h, t, m;
	scanf("%f %f %f", &h, &t, &m);
	float weight = h * t / 240;
	float index = m / ((h / 100) * (h / 100));
	printf("%.5f %.5f", weight, index);
	return 0;
}