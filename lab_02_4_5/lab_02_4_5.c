#include <stdio.h>
#define ARRAY_LENGHT 10
typedef enum
{
	success,
	incorrect_input,
	unsiutable_condition
} status_code;
status_code read_array(int **begin, int **end)
{
	int n;
	if (scanf("%d", &n) != 1)
		return incorrect_input;
	if (n < 1 || n > ARRAY_LENGHT)
		return incorrect_input;
	int count = 0;
	for (int i = 0; i < n; i++, (*end)++)
		count += scanf("%d", *end);
	char tmp;
	int rc = scanf("%c", &tmp);
	if (count != n || rc != EOF || *begin == *end)
		return incorrect_input;
	return success;
}
int check_array(int **begin, int **end)
{
	int count = 0, flag = 0;
	for (int *i = *begin; i < *end; i++)
	{
		for (int *j = i + 1; j < *end; j++)
			if (*i == *j)
			{
				flag = 1;
				break;
			}
		if (!flag)
			count++;
		flag = 0;
	}
	return count;
}
int main()
{
	int a[ARRAY_LENGHT], *begin = a, *end = a;
	status_code error = read_array(&begin, &end);
	if (error)
	{
		printf("Input error.");
		return error;
	}
	int r = check_array(&begin, &end); 
	printf("%d", r);
}