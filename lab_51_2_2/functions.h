#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#define SUCCESS 0
#define INCORRECT_INPUT 1
int avg_function(FILE *file, float *avg, int *count);
void disp_function(FILE *file, float *disp, float avg, int count);
#endif