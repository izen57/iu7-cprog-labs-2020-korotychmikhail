#ifndef __INOUT_H__
#define __INOUT_H__

#include <stdio.h>
#include <stdlib.h>

int **input(FILE *file, int *str, int *stb);
void output(int **matrix, int str, int stb);
int input_rho_and_gamma(int *rho, int *gamma);

#endif