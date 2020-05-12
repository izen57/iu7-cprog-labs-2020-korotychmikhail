#include <stdio.h>
#include <string.h>
#include <errno.h>
#define SUCCESS 0
#define INCORRECT_INPUT -1
int avg_function(FILE *file, float *avg, int *count)
{
	float num, sum = 0;
	while (fscanf(file, "%f", &num) == 1)
	{
		sum += num;
		(*count)++;
	}
	if (*count == 1)
		return INCORRECT_INPUT;
	else
	{
		*avg = sum / *count;
		return SUCCESS;
	}
}
void disp_function(FILE *file, float *disp, float avg, int count)
{
	float num, sum = 0;
	for (int i = 0; i < count; i++)
	{
		fscanf(file, "%f", &num);
		sum += (num - avg) * (num - avg);
	}
	*disp = sum / count;
}
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Not enough options: %s", strerror(errno));
		return INCORRECT_INPUT;
	}
	FILE *file;
	file = fopen(argv[2], "r");
	if (!file)
	{
		fprintf(stderr, "Unable to open file: %s", strerror(errno));
		return INCORRECT_INPUT;
	}
	float avg;
	int count = 0, error = avg_function(file, &avg, &count);
	if (error)
	{
		fprintf(stderr, "Incorrect input: %s", strerror(errno));
		return error;
	}
	float disp;
	disp_function(file, &disp, avg, count);
	fclose(file);
	fprintf(stdout, "%f", disp);
	return error;
}