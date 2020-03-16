#include <stdio.h>
#include <math.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
	unsiutable_condition
} status_code;
int digit_is_simple(int n)
{
	int count = 1;
	if (n < 2)
		return 0;
	for (int i = 1; i * i <= n; i++)
		if (n % i == 0)
			count++;
	if (count == 2)
		return 1;
	else
		return 0;
}
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
status_code calc(int a[ARRAY_LENGHT], int (*b)[ARRAY_LENGHT], int n, int *j)
{
	*j = 0;
	for (int i = 0; i < n; i++)
		if (digit_is_simple(a[i]))
		{
			(*b)[*j] = a[i];
			(*j)++;
		}
	if ((*j) == 0)
		return unsiutable_condition;
	else
		return success;
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
	int b[ARRAY_LENGHT], j;
	error = calc(a, &b, n, &j);
	if (error)
		printf("There are no such digits.");
	else
		for (int i = 0; i < j; i++)
			printf("%d ", b[i]);
	return error;
}