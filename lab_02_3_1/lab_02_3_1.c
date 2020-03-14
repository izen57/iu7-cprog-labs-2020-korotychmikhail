#include <stdio.h>
#include <math.h>
#define N 10

typedef enum {SUCCESS, INCORRECT_INPUT, UNSUITABLE_CONDITION} status_code;
status_code read_array(int (*a)[N], int *n)
{
	int count = 0;
	if (scanf("%d", n) != 1)
		return INCORRECT_INPUT;
	if (*n <= 0 || *n > N)
		return INCORRECT_INPUT;
	for (int i = 0; i < *n; i++)
		count += scanf("%d", &(*a)[i]);
	return SUCCESS;
}
status_code geometry_mean(int a[N], int n, float *geomean)
{
	*geomean = 1;
	int count = 0;
	for (int i = 0; i < n; i++)
		if (a[i] > 0)
		{
			count++;
			*geomean *= a[i];
		}
	if (count == 0)
		return UNSUITABLE_CONDITION;
	*geomean = sqrt(*geomean);
	return SUCCESS;
}
int main()
{
	int a[N], n;
	status_code error = read_array(&a, &n);
	if (error)
	{
		printf("Input error.");
		return error;
	}
	float geomean;
	error = geometry_mean(a, n, &geomean);
	if (error)
	{
		printf("Input error.");
		return error;
	}
	printf("%f", geomean);
	return SUCCESS;
}