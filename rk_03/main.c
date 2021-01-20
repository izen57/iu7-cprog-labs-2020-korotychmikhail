// вертикальная змейка
#include <stdio.h>
#include <stdlib.h>
int **allocate_matrix(int n, int m)
{
	int **ptrs, *matrix;
	ptrs = malloc(n * sizeof(int *));
	if (!ptrs)
		return NULL;
	matrix = malloc(n * m * sizeof(int));
	if (!matrix)
	{
		free(ptrs);
		return NULL;
	}
	for (int i = 0; i < n; i++)
		ptrs[i] = matrix + i * m;
	return ptrs;
}
void free_matrix(int **ptrs)
{
	free(ptrs[0]);
	free(ptrs);
}
int **input(int *str, int *stb)
{
	if (scanf("%d", str) == 1 && *str > 1 && *str < 100 && scanf("%d", stb) == 1 && *stb > 1 && *stb < 100)
	{
		printf("----\n");
		int **matrix = allocate_matrix(*str, *stb);
		if (!matrix)
			return NULL;
		for (int i = 0; i < *str; i++)
			for (int j = 0; j < *stb; j++)
				if (scanf("%d", &matrix[i][j]) != 1)
					return NULL;
		return matrix;
	}
	else
		return NULL;
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
int *ind(int **matrix, int ii, int n) 
{
    int *iP = matrix[ii / n];
    int j = ii % n;
    j = (ii / n) & 1? n - j - 1 : j;
    return iP + j;
}
void sort_bubble(int *matrix, int n)
{
	int temp;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1 - i; j++)
			if (matrix[j] > matrix[j + 1])
			{
				temp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = temp;
			}
}
void vertical_snake(int **matrix, int n, int m)
{
	/*for (int i = 0; i < n; i++)
		sort_bubble(matrix[i], n);
	printf("--sort--\n");
	output(matrix, n, m);
	printf("----\n");*/
	/*for(int k = 0; k < n * n; ++k)
		for(int i = 0; i < n - 1; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				if(j != n - 1)
				{
					if(matrix[j + 1][i] < matrix[j][i])
					{
						int tmp = matrix[j + 1][i];
						matrix[j + 1][i] = matrix[j][i];
						matrix[j][i] = tmp;
					}
				}
				else if((matrix[0][i + 1] < matrix[j][i]) && (i != n - 1))
				{
						int tmp = matrix[0][i + 1];
						matrix[0][i + 1] = matrix[j][i];
						matrix[j][i] = tmp;
				}
			}
		}
	int *b = calloc(m, sizeof(int));
	for(int i = 0; i < m; ++i) 
		if (i%2 == 1)
		{
			for(int j = 0; j < m; ++j) 
				b[j] =  matrix[j][i];
			for(int j = 0; j < m; ++j) 
				matrix[j][i] = b[m-j-1];
		}*/
	int flag = 1;
	while (flag) 
	{
		flag = 0;
		for (int i = 0; i < m * n - 1; i++) 
		{
			int *i1 = ind(matrix, i, n);
			int *i2 = ind(matrix, i + 1, n);
			if (*i1 > *i2)
			{
				flag = 1;
				int k = *i2;
				*i2 = *i1;
				*i1 = k;
			}
		}
	}
}
int main(void)
{
	int n, m;
	int **matrix = input(&n, &m);
	if (!matrix)
		return 1;
	output(matrix, n, m);
	printf("--out--\n");
	vertical_snake(matrix, n, m);

	output(matrix, n, m);
	free_matrix(matrix);
	return 0;
}