#include <stdlib.h>
#include <math.h>
#include <string.h>
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
		matrix = NULL;
	else
		for (int i = 0; i < str; i++)
		{
			int *temp = calloc(stb, sizeof(int));
			if (!temp)
			{
				free_matrix(matrix, str);
				matrix = NULL;
				break;
			}
			matrix[i] = calloc(stb, sizeof(int));
			free(temp);
		}
	return matrix;
}

void remove_str_shift(int **matrix, int str, int stb, int point)
{
	for (int i = point; i < str - 1; i++)
		memmove(matrix[i], matrix[i + 1], stb * sizeof(int));
}

int **remove_str(int **matrix, int *str, int stb)
{
	int max = NEG_INF, index;
	for (int i = 0; i < *str; i++)
		for (int j = 0; j < stb; j++)
			if (matrix[i][j] >= max)
			{
				max = matrix[i][j];
				index = i;
			}
	remove_str_shift(matrix, *str, stb, index);
	free(matrix[*str - 1]);
	int **temp = realloc(matrix, --(*str) * sizeof(int *));
	if (!temp)
	{
		free_matrix(matrix, *str + 1);
		matrix = NULL;
	}
	else
		matrix = temp;
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
	for (int i = 0; i < str; i++)
		for (int j = 0; j < *stb; j++)
			if (matrix[i][j] >= max)
			{
				max = matrix[i][j];
				index = j;
			}
	remove_stb_shift(matrix, str, *stb, index);
	(*stb)--;
	for (int i = 0; i < str; i++)
	{
		int *temp = realloc(matrix[i], *stb * sizeof(int));
		if (!temp)
		{
			free_matrix(matrix, str);
			matrix = NULL;
			break;
		}
		matrix[i] = temp;
	}
	return matrix;
}

int counting_low_average(int **matrix, int point, int stb)
{
	float summ = 0;
	for (int i = 0; i < point; i++)
		summ += matrix[i][stb];
	return (int) floor(summ / point);
}

int counting_minimum(int **matrix, int str, int point)
{
	int min = POS_INF;
	for (int i = 0; i < point; i++)
		if (matrix[str][i] < min)
			min = matrix[str][i];
	return min;
}

int **add_str_and_stb(int **matrix, int *str, int *stb, int amount)
{
	int **temp = realloc(matrix, amount * sizeof(int *));
	if (!temp)
	{
		free_matrix(matrix, *str);
		matrix = NULL;
	}
	else
	{
		matrix = temp;
		for (int i = *str; i < amount; i++)
		{
			int *temp = calloc(*stb, sizeof(int));
			if (!temp)
			{
				free_matrix(matrix, *str);
				matrix = NULL;
				break;
			}
			matrix[i] = calloc(*stb, sizeof(int));
			free(temp);
		}
		if (matrix)
		{
			for (int i = *str; i < amount; i++)
				for (int j = 0; j < *stb; j++)
					matrix[i][j] = counting_low_average(matrix, i, j);
			*str += amount - *str;
			for (int i = 0; i < amount; i++)
			{
				int *temp_elem = realloc(matrix[i], amount * sizeof(int));
				if (!temp_elem)
				{
					free_matrix(matrix, *str);
					matrix = NULL;
					break;
				}
				matrix[i] = temp_elem;
				for (int j = *stb; j < amount; j++)
					matrix[i][j] = counting_minimum(matrix, i, j);
			}
			if (matrix)
				*stb += amount - *stb;
		}
	}
	return matrix;
}

int **multiplication(int **matrix1, int str1, int stb1, int **matrix2, int str2, int stb2)
{
	int **result;
	if (str1 != stb2)
	{
		free_matrix(matrix1, str1);
		free_matrix(matrix2, str2);
		result = NULL;
	}
	else
	{
		result = allocate_matrix(str1, stb2);
		if (!result)
		{
			free_matrix(matrix1, str1);
			free_matrix(matrix2, str2);
		}
		else
			for (int i = 0; i < str1; i++)
				for (int j = 0; j < stb2; j++)
				{
					result[i][j] = 0;
					for (int k = 0; k < stb1; k++)
						result[i][j] += matrix1[i][k] * matrix2[k][j];
				}
	}
	return result;
}

int **remove_by_number(int **matrix, int *rows, int *cols, int number)
{
	if (*rows > *cols)
		while (*rows > number)
		{
			matrix = remove_str(matrix, rows, *cols);
			if (!matrix)
				break;
		}
	else if (*cols > *rows)
		while (*cols > number)
		{
			matrix = remove_stb(matrix, *rows, cols);
			if (!matrix)
				break;
		}
	return matrix;
}

int **add_by_number(int **matrix, int *rows, int *cols, int number)
{
	if (number > *rows)
	{
		matrix = add_str_and_stb(matrix, rows, cols, number);
		/*if (!matrix)
			return NULL;*/
	}
	return matrix;
}