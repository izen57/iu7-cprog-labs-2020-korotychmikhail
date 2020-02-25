#include <stdio.h>
int fnc(int x1, int x2, int y1, int y2, int x3, int y3, int x4, int y4)
{
	char x = 'f', y = 'f';
	if (x1 >= x2)
	{
		float temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	if (x3 >= x4)
	{
		float temp = x3;
		x3 = x4;
		x4 = temp;
		temp = y3;
		y3 = y4;
		y4 = temp;
	}
	float k1 = (y2 - y1) / (x2 - x1), k2 = (y4 - y3) / (x4 - x3);
	if (k1 == k2)
		printf("0");
	else
	{
		float b1 = y1 - k1 * x1, b2 = y3 - k2 * x3;
		float x0 = (b2 - b1) / (k1 - k2);
		x = x0 + '0';
		float y0 = k1 * x0 + b1;
		y = y0 + '0';
		if (x != 'f' && y != 'f')
			printf("1");
	}
}
int main()
{
	float x1, y1, x2, y2, x3, y3, x4, y4;
	if (scanf("%f %f %f %f %f %f %f %f", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4) == 8)
	{
		fnc(x1, x2, y1, y2, x3, y3, x4, y4);
		return 0;
	}
	else
	{
		printf("Input error.");
		return 1;
	}
}