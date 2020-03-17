#include <stdio.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
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
void sort((*a)[ARRAY_LENGHT], int n)
{
	int j = 0, current = 0;
	for (int i = 0; i < n; i++)
	{
		current = (*a)[i];
		j = i;
		while ((*a)[j - 1] > current && j > 0)
		{
			(*a)[j] = (*a)[j - 1];
			j--;
		}
		(*a)[j] = current;
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
	sort(&a, n);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
}