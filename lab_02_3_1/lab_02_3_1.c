#include <stdio.h>
#include <math.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
	unsiutable_condition
} status_code;
status_code read_array(int (*a)[ARRAY_LENGHT], int *n)
{
	if (scanf("%d", n) != 1)
		return incorrect_input;
	if (*n < 1 || *n > ARRAY_LENGHT)
		return incorrect_input;
	int count = 0;
	for (int i = 0; i < *n; i++)
		count += scanf("%d", &(*a)[i]);
	char tmp;
	int rc = scanf("%c", &tmp);
	if (count != *n || rc != EOF)
		return incorrect_input;
	return success;
}
status_code geometry_mean(int a[ARRAY_LENGHT], int n, float *geomean)
{
	int count = 0;
	*geomean = 1;
	for (int i = 0; i < n; i++)
		if (a[i] > 0)
		{
			count++;
			*geomean *= a[i];
		}
	if (count == 0)
		return unsiutable_condition;
	else
	{
		*geomean = pow(*geomean, 1.0 / count);
		return success;
	}
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
		printf("Input error.");
	else
		printf("%f", geomean);
	return error;
}