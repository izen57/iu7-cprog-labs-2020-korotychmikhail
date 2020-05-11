#include <stdio.h>
#include "process.h"
int main(void)
{
	int max = 1, error = process(stdin, &max);
	if (!error)
		fprintf(stdout, "%d", max);
	return error;
}