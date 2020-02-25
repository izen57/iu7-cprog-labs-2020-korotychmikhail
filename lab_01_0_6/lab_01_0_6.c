#include <stdio.h>
#include <math.h>

int fnc(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	float b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	float c = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
	
	if (a >= b + c || b >= a + c || c >= a + b)
	{
		printf("Input error.");
		return 1;
	}
	else if (a * a == b * b + c * c || b * b == a * a + c * c || c * c == b * b + a * a)
	{
		printf("1");
		return 0;
	}
	else if (a * a > b * b + c * c || b * b > a * a + c * c || c * c > b * b + a * a)
	{
		printf("2");
		return 0;
	}
	else
	{
		printf("0");
		return 0;
	}
}
int main()
{
	float x1, y1, x2, y2, x3, y3;
	if (scanf("%f %f %f %f %f %f", &x1, &y1, &x2, &y2, &x3, &y3) == 6)
	{
		int a = fnc(x1, y1, x2, y2, x3, y3);
		return a;
	}
	else
	{
		printf("Input error.");
		return 1;
	}
}