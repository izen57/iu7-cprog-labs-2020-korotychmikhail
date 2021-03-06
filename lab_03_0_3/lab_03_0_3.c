#include <stdio.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
} status_code;
status_code read_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int *n, int *m)
{
	if (scanf("%d %d", n, m) != 2 || *n < 2 || *m < 2 || *n > ARRAY_LENGHT || *m > ARRAY_LENGHT)
		return incorrect_input;
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *m; j++)
			if (scanf("%d", &a[i][j]) != 1)
				return incorrect_input;
	return success;
}
int sum(int a[ARRAY_LENGHT][ARRAY_LENGHT], int i, int m)
{
	int sum = 0;
	for (int j = 0; j < m; j++)
		sum += a[i][j];
	return sum;
}
void change_places(int a[ARRAY_LENGHT][ARRAY_LENGHT], int curr, int next, int m)
{
	int temp[ARRAY_LENGHT];
	for (int j = 0; j < m; j++)
		temp[j] = a[curr][j];
	for (int j = 0; j < m; j++)
		a[curr][j] = a[next][j];
	for (int j = 0; j < m; j++)
		a[next][j] = temp[j];
}
void print_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			printf("%d\n", a[i][j]);
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
	for (int i = 0; i < n - 1; i++)
	{
		int flag = 0;
		for (int j = 0; j < n - i - 1; j++)
			if (sum(a, j, m) > sum(a, j + 1, m))
			{
				flag = 1;
				change_places(a, j, j + 1, m);
			}
		if (flag == 0)
			break;
	}
	print_array(a, n, m);
	return success;
}