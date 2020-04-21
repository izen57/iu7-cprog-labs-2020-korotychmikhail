#include <stdio.h>
#include <string.h>
#include "my_strcspn.h"
#define LINE_LENGHT 256
typedef enum
{
	success,
	incorrect_input,
	unsuitable_condition
} status_code;
status_code read_line(char a[LINE_LENGHT + 1], int *n)
{
	int ch;
	while ((ch = getchar()) != '\n' || ch != EOF || *n < LINE_LENGHT)
		a[(*n)++] = ch;
	a[*n] = '\0';
	if (a[0] == '\0')
		return incorrect_input;
	else
		return success;
}
status_code read_keys(char b[LINE_LENGHT + 1], int *m)
{
	int ch;
	while ((ch = getchar()) != '\n' || ch != EOF || *m < LINE_LENGHT)
		b[(*m)++] = ch;
	b[*m] = '\0';
	if (b[0] == '\0')
		return incorrect_input;
	else
		return success;
}
int main(void)
{
	char a[LINE_LENGHT + 1];
	int n = 0, getchar(void);
	status_code error = read_line(a, &n);
	if (error)
	{
		//printf("1");
		return error;
	}
	char b[LINE_LENGHT + 1];
	int m = 0;
	error = read_keys(b, &m);
	if (error)
	{
		//printf("2");
		return error;
	}
	int res = strcspn(a, b);
	printf("%d\n", res);
	my_strcspn(a, b, n);
	//printf("3");
	return success;
}