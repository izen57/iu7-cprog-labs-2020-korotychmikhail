#include <stdio.h>
#include <math.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
	unsiutable_condition
} status_code;
int digit_is_palindrom(int n)
{
	if (n < 0)
		return 0;
	if (n >= 0 && n < ARRAY_LENGHT)
		return 1;
	int x = n, sum = 0;
	while (x != 0)
	{
		sum = (sum * 10) + (n % 10);
		x /= 10;
	}
	if (sum == n)
		return 1;
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
status_code calc(int (*a)[ARRAY_LENGHT], int n, int *count)
{
	*count = 0;
	for (int i = 0; i < n; i++)
		if (digit_is_palindrom((*a)[i]))
		{
			(*a)[i] = 0;
			(*count)++;
		}
	if ((*count) == 0)
		return unsiutable_condition;
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
	int count;
	error = calc(&a, n, &count);
	if (error)
		printf("There are not such digits.");
	else
		for (int i = 0; i < n; i++)
			if (a[i] != 0)
				printf("%d", a[i]);
	return error;
}