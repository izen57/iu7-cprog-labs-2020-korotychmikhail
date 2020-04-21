#define __USE_MINGW_ANSI_STDIO 1 
#include <stdio.h>
#include <string.h>
#include "my_strcspn.h"
int main(void)
{
	char a[LINE_LENGHT + 1];
	char b[LINE_LENGHT + 1];
	printf("%ld\n", strcspn(a, b));
	status_code error = my_strcspn(a, b);
	return error;
}