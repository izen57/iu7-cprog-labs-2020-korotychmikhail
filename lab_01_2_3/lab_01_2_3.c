#include <stdio.h>
int main()
{
	float r1, r2, r3;
	scanf("%f %f %f", &r1, &r2, &r3);
	float r = r1 * r2 *r3 / (r2 * r3 + r1 * r3 + r1 * r2);
	printf("%.5f", r);
	return 0;
}