#define __USE_MINGW_ANSI_STDIO 1 
#include <stdio.h>
#include <string.h>
#include "my_strcspn.h"
int main(void)
{
	char a[LINE_LENGHT + 1];
	char b[LINE_LENGHT + 1];
	printf("%ld\n", strcspn(a, b));
	my_strcspn(a, b);
	//printf("3");
	return success;
}