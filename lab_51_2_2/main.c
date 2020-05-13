#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "functions.h"
int main(int argc, char **argv)
{
	FILE *file;
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Unable to open file: %s", strerror(errno));
		return INCORRECT_INPUT;
	}
	float avg;
	int count = 0, error = avg_function(file, &avg, &count);
	if (error)
		return error;
	float disp;
	rewind(file);
	disp_function(file, &disp, avg, count);
	fclose(file);
	fprintf(stdout, "%f", disp);
	return SUCCESS;
}