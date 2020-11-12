#ifndef __INOUT_H__
#define __INOUT_H__
#include <stdio.h>
int counting_numbers(FILE *file, int *n);
int read_array(FILE *file, int **begin, int **end);
void output(FILE *file, int *begin, int *end);
#endif