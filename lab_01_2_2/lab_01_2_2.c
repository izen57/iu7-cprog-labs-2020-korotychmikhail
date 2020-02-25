#include <stdio.h>
#include <math.h>

const float pi = 3.14159;
int main()
{
	float x1, y1, x2, y2, x3, y3;
	scanf("%f %f %f %f %f %f", &x1, &y2, &x2, &y2, &x3, &y3);
	float ab = sqrt((x1 - x2) * (x1 - x2)+ (y1 - y2) * (y1 - y2));
	float bc  = sqrt((x2 - x3) * (x2 - x3)+ (y2 - y3) * (y2 - y3));
	float ac = sqrt((x3 - x1) * (x3 - x1)+ (y3 - y1) * (y3 - y1));
	float p = ab + bc + ac;
	printf("%.5f", p);
	return 0;
}