#include <stdio.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
} status_code;
status_code read_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int *n, int *m)
{
	if (scanf("%d %d", n, m) != 2 || *n < 2 || *m < 1 || *n > ARRAY_LENGHT || *m > ARRAY_LENGHT)
		return incorrect_input;
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *m; j++)
			if (scanf("%d", &a[i][j]) != 1)
				return incorrect_input;
	/*char tmp;
	//int rc = scanf("%c", &tmp);
	if (count != *n * *m || rc != EOF)
		return incorrect_input;*/
	return success;
}
void check_array(int a[ARRAY_LENGHT][ARRAY_LENGHT], int b[ARRAY_LENGHT], int n, int m)
{
	for (int i = 0; i < m; i++)
	{
		int count = 0;
		for (int j = 0; j < n - 1; j++)
			if (a[j][i] >= a[j + 1][i])
				count++;
		if (count == n - 1)
			b[i] = 1;
		else
			b[i] = 0;
	}
}
void print_array(int b[ARRAY_LENGHT], int m)
{
	for (int i = 0; i < m; i++)
		printf("%d\n", b[i]);
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
	int b[ARRAY_LENGHT];
	check_array(a, b, n, m);
	print_array(b, m);
	return success;
}