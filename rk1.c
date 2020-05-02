#include <stdio.h>
#define ARRAY_LENGHT 20
typedef enum
{
	success,
	incorrect_input
} status_code;
status_code input(int a[ARRAY_LENGHT], int *n, int *k)
{
	if (scanf("%d", n) != 1 || *n > ARRAY_LENGHT || *n < 2)
		return incorrect_input;
	for (int i = 0; i < *n; i++)
		if (scanf("%d", &a[i]) != 1)
			return incorrect_input;
	if (scanf("%d", k) != 1 || *k < 1)
		return incorrect_input;
	return success;
}
void del(int a[ARRAY_LENGHT], int *n, int h)
{
	
}
void checking(int a[ARRAY_LENGHT], int *n, int k)
{
	for (int i = 0; i < *n; i += 3)
		if (a[i] % k == 0)
		{
			for (int j = i; j < *n; j++)
				a[j] = a[j + 1];
			(*n)--;
			i--;
		}
}
void output(int a[ARRAY_LENGHT], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
}
int main(void)
{
	int a[ARRAY_LENGHT], n, k;
	if (input(a, &n, &k))
		return incorrect_input;
	checking(a, &n, k);
	output(a, n);
	return success;
}