#include <stdlib.h>
#include <math.h>
#include "../inc/error_codes.h"
void free_matrix(int **matrix, int str)
{
	for (int i = 0; i < str; i++)
		free(matrix[i]);
	free(matrix);
}
int **allocate_matrix(int str, int stb)
{
	int **matrix = calloc(str, sizeof(int *));
	if (!matrix)
		return NULL;
	for (int i = 0; i < str; i++)
	{
		matrix[i] = calloc(stb, sizeof(int));
		if (!matrix[i])
		{
			free_matrix(matrix, str);
			return NULL;
		}
	}
	return matrix;
}
void remove_str_shift(int **matrix, int str, int point)
{
	for (int i = point; i < str - 1; i++)
		matrix[i] = matrix[i + 1];
}
int **remove_str(int **matrix, int *str, int stb)
{
	int max = NEG_INF, index;
	for (int i = *str - 1; i >= 0; i--)
		for (int j = stb - 1; j >= 0; j--)
			if (matrix[i][j] > max)
			{
				max = matrix[i][j];
				index = i;
			}
	remove_str_shift(matrix, *str, index);
	matrix = realloc(matrix, --(*str) * sizeof(int *));
	if (!matrix)
	{
		free_matrix(matrix, *str);
		return NULL;
	}
	return matrix;
}
void remove_stb_shift(int **matrix, int str, int stb, int point)
{
	for (int i = 0; i < str; i++)
		for (int j = point; j < stb - 1; j++)
			matrix[i][j] = matrix[i][j + 1];
}
int **remove_stb(int **matrix, int str, int *stb)
{
	int max = NEG_INF, index;
	for (int i = str - 1; i >= 0; i--)
		for (int j = *stb - 1; j >= 0; j--)
			if (matrix[i][j] > max)
			{
				max = matrix[i][j];
				index = j;
			}
	remove_stb_shift(matrix, str, *stb, index);
	(*stb)--;
	for (int i = 0; i < str; i++)
	{
		matrix[i] = realloc(matrix[i], *stb * sizeof(int));
		if (!matrix[i])
		{
			free_matrix(matrix, str);
			return NULL;
		}
	}
	return matrix;
}
int counting_low_average(int **matrix, int str, int stb)
{
	int summ = 0;
	for (int i = 0; i < str - 1; i++)
		summ += matrix[i][stb];
	return (int)floor(summ / (str - 1));
}
int counting_minimum(int **matrix, int str, int stb)
{
	int min = POS_INF;
	for (int i = 0; i < stb - 1; i++)
		if (matrix[str][i] < min)
			min = matrix[str][i];
	return min;
}
int **add_str_and_stb(int **matrix, int *str, int *stb)
{
	// matrix[*str - 1] = (int *)((char *)matrix + *str * sizeof(int *) + (*str - 1) * *stb * sizeof(int));
	matrix[(*str)++] = calloc(*stb, sizeof(int));
	if (!matrix[*str - 1])
		return NULL;
	for (int i = 0; i < *stb; i++)
		matrix[*str - 1][i] = counting_low_average(matrix, *str, i);
	(*stb)++;
	for (int i = 0; i < *str; i++)
	{
		// matrix[i] = (int *)((char *)matrix + *str * sizeof(int *) + i * *stb * sizeof(int));
		matrix[i] = realloc(matrix[i], *stb * sizeof(int));
		if (!matrix[i])
			return NULL;
		matrix[i][*stb - 1] = counting_minimum(matrix, i, *stb);
	}
	return matrix;
}
int **multiplication(int **matrix1, int str1, int stb1, int **matrix2, int str2, int stb2)
{
	if (stb1 != str2)
		return NULL;
	int **result = allocate_matrix(str1, stb2);
	if (!result)
		return NULL;
	for (int i = 0; i < str1; i++)
		for (int j = 0; j < stb2; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < stb1; k++)
				result[i][j] += matrix1[i][k] * matrix2[k][j];
		}
	return result;
}