#include <stdio.h>
#include <math.h>
const float pi = 3.14159;
int main()
{
	float a, b, alpha;
	scanf("%f %f %f", &a, &b, &alpha);
	float s = a * b / sin(alpha * pi / 180);
	printf("%.5f", s);
	return 0;
}