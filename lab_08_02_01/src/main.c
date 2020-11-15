#include <stdio.h>
#include <stdlib.h>
#include "../inc/inout.h"
#include "../inc/error_codes.h"
#include "../inc/task.h"
int main(void)
{
	int error = SUCCESS;
	int n, m;
	int **a = input(&n, &m);
	if (!a)
		return INPUT_ERROR;
	/*output(a, n, m);
	printf("----\n");*/
	int p, q;
	int **b = input(&p, &q);
	if (!b)
	{
		free_matrix(a, n);
		return INPUT_ERROR;
	}
	/*output(b, p, q);
	printf("----\n");*/
	int k = m < n ? m : n;
	int s = p < q ? p : q;
	a = remove_by_number(a, &n, &m, k);
	if (!a)
	{
		free_matrix(b, p);
		return ALLOCATE_ERROR;
	}
	b = remove_by_number(b, &p, &q, s);
	if (!b)
	{
		free_matrix(a, n);
		return ALLOCATE_ERROR;
	}
	/*output(a, n, m);
	printf("----\n");
	output(b, p, q);*/
	int rho, gamma;
	if (input_rho_and_gamma(&rho, &gamma))
	{
		free_matrix(a, n);
		free_matrix(b, p);
		return INPUT_ERROR;
	}
	int z = k > s ? k : s;
	a = add_by_number(a, &n, &m, z);
	if (!a)
	{
		free_matrix(b, p);
		return ALLOCATE_ERROR;
	}
	b = add_by_number(b, &p, &q, z);
	if (!b)
	{
		free_matrix(a, n);
		return ALLOCATE_ERROR;
	}
	/*output(a, n, m);
	printf("----\n");
	output(b, p, q);*/
	if (!rho && n == m)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				if (i == j)
					a[i][j] = 1;
				else
					a[i][j] = 0;
			}
	}
	else if (rho)
	{
		int **temp = allocate_matrix(n, m);
		if (!temp)
		{
			free_matrix(a, n);
			free_matrix(b, p);
			return ALLOCATE_ERROR;
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				temp[i][j] = a[i][j];
		for (int i = 0; i < rho - 1; i++)
		{
			a = multiplication(a, n, m, temp, n, m);
			if (!a)
			{
				free_matrix(temp, n);
				free_matrix(b, p);
				return ALLOCATE_ERROR;
			}
		}
		free_matrix(temp, n);
	}
	else if (!rho)
	{
		free_matrix(a, n);
		free_matrix(b, p);
		return INPUT_ERROR;
	}
	if (!gamma && p == q)
	{
		for (int i = 0; i < p; i++)
			for (int j = 0; j < q; j++)
			{
				if (i == j)
					b[i][j] = 1;
				else
					b[i][j] = 0;
			}
	}
	else if (gamma)
	{
		int **temp = allocate_matrix(p, q);
		if (!temp)
		{
			free_matrix(a, n);
			free_matrix(b, p);
			return ALLOCATE_ERROR;
		}
		for (int i = 0; i < p; i++)
			for (int j = 0; j < q; j++)
				temp[i][j] = b[i][j];
		for (int i = 0; i < gamma - 1; i++)
		{
			b = multiplication(b, p, q, temp, p, q);
			if (!b)
			{
				free_matrix(temp, p);
				free_matrix(a, n);
				return ALLOCATE_ERROR;
			}
		}
		free_matrix(temp, p);
	}
	else if (!gamma)
	{
		free_matrix(a, n);
		free_matrix(b, p);
		return INPUT_ERROR;
	}
	int **result = multiplication(a, n, m, b, p, q);
	//printf("--multiplication--\n");
	output(result, n, q);
	free_matrix(a, n);
	free_matrix(b, p);
	free_matrix(result, n);
	return error;
}