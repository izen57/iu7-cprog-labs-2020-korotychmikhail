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
	if (scanf("%d %d", n, m) != 2 || *n < 1 || *m < 1 || *n > ARRAY_LENGHT || *m > ARRAY_LENGHT)
		return incorrect_input;
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *m; j++)
			if (scanf("%d", &a[i][j]) != 1)
				return incorrect_input;
	return success;
}
int sum_of_digits(int n)
{
	int x = n, sum = 0;
	while (x)
	{
		sum += x % 10;
		x /= 10;
	}
	return sum;
}
status_code check_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int n, int m)
{
	int b[ARRAY_LENGHT*ARRAY_LENGHT], k = 0, count = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (sum_of_digits(a[i][j]) > 10)
			{
				count++;
				b[k] = a[i][j];
				a[i][j] = -1000;
				k++;
			}
	if (count == 0)
		return unsuitable_condition;
	else
	{
		for (int i = 0; i < 3; i++)
		{
			int temp = b[0];
			for (int j = 1; j < count; j++)
				b[j - 1] = b[j];
			b[count - 1] = temp;
		}
		k = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (a[i][j] == -1000)
				{
					a[i][j] = b[k];
					k++;
				}
		return success;
	}
}
void print_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			printf("%d\n", a[i][j]);
}
int main()
{
	int a[ARRAY_LENGHT][ARRAY_LENGHT], n, m;
	status_code error = read_array(a, &n, &m);
	if (error)
	{
		printf("Input error.");
		return error;
	}
	error = check_array(a, n, m);
	if (error)
		return error;
	else
	{
		print_array(a, n, m);
		return success;
	}
}