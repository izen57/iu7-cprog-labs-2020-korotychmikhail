#include <stdio.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
	unsuitable_condition
} status_code;
status_code read_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int *n, int *m)
{
	if (scanf("%d %d", n, m) != 2 || *n != *m || *n < 1 || *n > ARRAY_LENGHT)
		return incorrect_input;
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *m; j++)
			if (scanf("%d", &a[i][j]) != 1)
				return incorrect_input;
	return success;
}
status_code min_odd(int a[ARRAY_LENGHT][ARRAY_LENGHT], int n)
{
	int min_odd = 100000;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i > j && a[i][j] % 2 != 0 && a[i][j] < min_odd)
				min_odd = a[i][j];
	if (min_odd == 100000)
		return unsuitable_condition;
	else
	{
		printf("%d", min_odd);
		return success;
	}
}
int main(void)
{
	int a[ARRAY_LENGHT][ARRAY_LENGHT], n, m;
	status_code error = read_array(a, &n, &m);
	if (error)
	{
		printf("Input error.");
		return error;
	}
	error = min_odd(a, n);
	if (error)
		return error;
}