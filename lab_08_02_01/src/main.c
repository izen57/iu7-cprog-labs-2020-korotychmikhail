#include <stdio.h>
#include <stdlib.h>
#include "../inc/inout.h"
#include "../inc/error_codes.h"
#include "../inc/task.h"
int main(void)
{
	int error = SUCCESS;
	int n, m;
	int **a = input(&m, &n);
	if (!a)
		return INPUT_ERROR;
	/*output(a, n, m);
	printf("----\n");*/
	int p, q;
	int **b = input(&p, &q);
	if (!b)
	{
		free_matrix(a, m);
		return INPUT_ERROR;
	}
	/*output(b, p, q);
	printf("----\n");*/
	int k = m < n ? m : n;
	int s = p < q ? p : q;
	a = remove_by_number(a, &m, &n, k);
	if (!a)
	{
		free_matrix(b, p);
		return ALLOCATE_ERROR;
	}
	b = remove_by_number(b, &p, &q, s);
	if (!b)
	{
		free_matrix(a, m);
		return ALLOCATE_ERROR;
	}
	/*output(a, n, m);
	printf("----\n");
	output(b, p, q);*/
	int rho, gamma;
	if (input_rho_and_gamma(&rho, &gamma))
	{
		free_matrix(a, m);
		free_matrix(b, p);
		return INPUT_ERROR;
	}
	int z = k > s ? k : s;
	a = add_by_number(a, &m, &n, z);
	if (!a)
	{
		free_matrix(b, p);
		return ALLOCATE_ERROR;
	}
	b = add_by_number(b, &p, &q, z);
	if (!b)
	{
		free_matrix(a, m);
		return ALLOCATE_ERROR;
	}
	/*output(a, n, m);
	printf("----\n");
	output(b, p, q);*/
	if (!rho && n == m)
	{
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				if (i == j)
					a[i][j] = 1;
				else
					a[i][j] = 0;
			}
	}
	else if (rho)
	{
		int **temp = allocate_matrix(m, n);
		if (!temp)
		{
			free_matrix(a, m);
			free_matrix(b, p);
			return ALLOCATE_ERROR;
		}
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				temp[i][j] = a[i][j];
		for (int i = 0; i < rho - 1; i++)
		{
			a = multiplication(a, m, n, temp, m, n);
			if (!a)
			{
				free_matrix(b, p);
				return ALLOCATE_ERROR;
			}
		}
		free_matrix(temp, m);
	}
	else if (!rho)
	{
		free_matrix(a, m);
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
			free_matrix(a, m);
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
				free_matrix(a, m);
				return ALLOCATE_ERROR;
			}
		}
		free_matrix(temp, p);
	}
	else if (!gamma)
	{
		free_matrix(a, m);
		free_matrix(b, p);
		return INPUT_ERROR;
	}
	int **result = multiplication(a, m, n, b, p, q);
	//printf("--multiplication--\n");
	output(result, m, q);
	free_matrix(a, m);
	free_matrix(b, p);
	free_matrix(result, m);
	return error;
}