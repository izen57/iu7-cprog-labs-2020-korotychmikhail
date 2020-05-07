#include <stdio.h>
#define ARRAY_LENGHT 20
typedef enum
{
	success,
	incorrect_input
} status_code;
status_code input(int m[ARRAY_LENGHT][ARRAY_LENGHT], int *n)
{
	if (scanf("%d", n) != 1 || *n > ARRAY_LENGHT || *n < 2)
		return incorrect_input;
	for (int i = 0; i < *n; i++)
		for (int j = 0; j < *n; j++)
			if (scanf("%d", &m[i][j]) != 1)
				return incorrect_input;
	return success;
}
int diag(int m[ARRAY_LENGHT][ARRAY_LENGHT], int start, int end, int n)
{
	int top_sum = 0 , down_sum = 0;
	for (int i = start; i < end; i++)
		for(int j = start + 1; j < (ARRAY_LENGHT - n) / 2; j++)
		{
			if (i < j)
				top_sum += m[i][j];
			else if (i < j)
				down_sum += m[i][j];
		}
	if (top_sum == down_sum)
		return 1;
	else
		return 0;
}
void checking(int m[ARRAY_LENGHT][ARRAY_LENGHT], int n)
{
	int index = 0;
	for (int i = n; i >= 0; i--)
		for (int j = n; j >= 0; j--)
			if (i == j)
			{
				if (diag(m, 0, n - 1, n))
					printf("%d", index);
				else
					index++;
			}
}
int main(void)
{
	int m[ARRAY_LENGHT][ARRAY_LENGHT], n;
	if (input(m, &n))
		return incorrect_input;
	checking(m, n);
}