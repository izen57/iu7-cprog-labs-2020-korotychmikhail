#include <stdio.h>
#include <math.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
	unsiutable_condition
} status_code;
int dig_is_simple(int n)
{
	if (n < 2)
		return 0;
	for(int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;
	return 1;
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
status_code calc(int a[ARRAY_LENGHT], int (*b)[ARRAY_LENGHT], int n, int *count)
{
	*count = 0;
	int j = 0;
	for (int i = 0; i < n; i++)
		if (dig_is_simple(a[i]))
		{
			(*count)++;
			(*b)[j] = a[i];
			j++;
		}
	if (*count == 0)
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
	int b[ARRAY_LENGHT], count;
	error = calc(a, &b, n, &count);
	if (error)
		printf("There are no such digits.");
	else
		for (int i = 0; i < count; i++)
			printf("%d ", b[i]);
	return error;
}