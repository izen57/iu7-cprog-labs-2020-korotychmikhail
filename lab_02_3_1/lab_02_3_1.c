#include <stdio.h>
#include <math.h>
#define ARRAY_LENGHT 10
typedef enum
{
	suсcess = 0,
	incorrect_input,
	unsiutable_condition
} status_code;
status_code read_array(int (*a)[ARRAY_LENGHT], int *n)
{
	int count = 0;
	if (scanf("%d", n) != 1)
		return incorrect_input;
	if (*n <= 0 || *n > ARRAY_LENGHT)
		return incorrect_input;
	for (int i = 0; i < *n; i++)
		count += scanf("%d", &(*a)[i]);
	return suсcess;
}
status_code geometry_mean(int a[ARRAY_LENGHT], int n, float *geomean)
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
		return unsiutable_condition;
	*geomean = sqrt(*geomean);
	return suсcess;
}
int main()
{
	int a[ARRAY_LENGHT], n;
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
	printf("%d", geomean);
	return suсcess;
}