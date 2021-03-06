#include <stdio.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
	unsuitable_condition
} status_code;
status_code read_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int *n, int *m, int *num)
{
	if (scanf("%d %d", n, m) != 2 || *n < 1 || *m < 1 || *n > ARRAY_LENGHT || *m > ARRAY_LENGHT)
		return incorrect_input;
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *m; j++)
			if (scanf("%d", &a[i][j]) != 1)
				return incorrect_input;
	if (scanf("%d", num) != 1 || *num > 9 || *num < 0)
		return incorrect_input;
	return success;
}
int first_num(int x)
{
	int n = 0;
	if (x < 0)
		x *= -1;
	while (x)
	{
		n = x % 10;
		x /= 10;
	}
	return n;
}
void shift(int a[ARRAY_LENGHT][ARRAY_LENGHT], int *n, int m, int op)
{
	(*n)++;
	for (int i = *n - 1; i > op; i--)
		for (int j = 0; j < m; j++)
			a[i][j] = a[i - 1][j];
	for (int j = 0; j < m; j++)
		a[op + 1][j] = 100;
}
void check_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int *n, int m, int num)
{
	for (int i = 0; i < *n; i++)
	{
		int countfn = 0, countln = 0; 
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] % 10 == num || -a[i][j] % 10 == num)
				countln++;
			int x = a[i][j];
			int first_number = first_num(x);
			if (first_number == num)
				countfn++;
		}
		if (countfn == countln && countfn > 0 && countln > 0)
		{
			shift(a, n, m, i);
			i++;
		}
	}
}
void print_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			printf("%d\n", a[i][j]);
}
int main(void)
{
	int a[ARRAY_LENGHT][ARRAY_LENGHT], n, m, num;
	status_code error = read_array(a, &n, &m, &num);
	if (error)
	{
		printf("Input error.");
		return error;
	}
	check_array(a, &n, m, num);
	print_array(a, n, m);
	return success;
}