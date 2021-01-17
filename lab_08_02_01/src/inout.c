#include <stdio.h>
#include <stdlib.h>
#include "../inc/inout.h"
#include "../inc/task.h"
#include "../inc/error_codes.h"

int **input(int *str, int *stb)
{
	int **matrix = NULL;
	if (scanf("%d", str) == 1 && *str > 1 && scanf("%d", stb) == 1 && *stb > 1)
	{
		matrix = allocate_matrix(*str, *stb);
		if (matrix)
			for (int i = 0; i < *str; i++)
			{
				for (int j = 0; j < *stb - 1; j++)
					if (scanf("%d", &matrix[i][j]) != 1)
					{
						free_matrix(matrix, *str);
						matrix = NULL;
						break;
					}
				if (matrix && scanf("%d\n", &matrix[i][*stb - 1]) != 1)
				{
					free_matrix(matrix, *str);
					matrix = NULL;
					break;
				}
			}
	}
	return matrix;
}

void output(int **matrix, int str, int stb)
{
	for (int i = 0; i < str; i++)
	{
		for (int j = 0; j < stb - 1; j++)
			printf("%d ", matrix[i][j]);
		printf("%d\n", matrix[i][stb - 1]);
	}
}

int input_rho_and_gamma(int *rho, int *gamma)
{
	int error = SUCCESS;
	if (scanf("%d", rho) != 1 || *rho < 0 || scanf("%d", gamma) != 1 || *gamma < 0)
		error = INPUT_ERROR;
	return error;
}