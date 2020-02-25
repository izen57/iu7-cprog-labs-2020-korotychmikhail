#include <stdio.h>

int main()
{
	float h, t, m;
	scanf("%f %f %f", &h, &t, &m);
	printf("%.5f %.5f", h * t / 240, m / ((h / 100) * (h / 100)));
	return 0;
}