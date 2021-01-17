#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/inout.h"
#include "../inc/error_codes.h"
#include "../inc/task.h"

void identity_matrix(int **matrix, int rows, int cols);
void copying(int **matrix1, int **matrix2, int rows, int cols);

int main(void)
{
	int error = SUCCESS;
	int n, m;
	int **a = input(&n, &m);
	if (!a)
		error = INPUT_ERROR;
	else
	{
		/*output(a, n, m);
		printf("----\n");*/
		int p, q;
		int **b = input(&p, &q);
		if (!b)
		{
			free_matrix(a, n);
			error = INPUT_ERROR;
		}
		else
		{
			/*output(b, p, q);
			printf("----\n");*/
			int k = m < n ? m : n;
			int s = p < q ? p : q;
			a = remove_by_number(a, &n, &m, k);
			if (!a)
			{
				free_matrix(b, p);
				error = ALLOCATE_ERROR;
			}
			else
			{
				b = remove_by_number(b, &p, &q, s);
				if (!b)
				{
					free_matrix(a, n);
					error = ALLOCATE_ERROR;
				}
				else
				{
					/*output(a, n, m);
					printf("----\n");
					output(b, p, q);*/
					int rho, gamma;
					if (input_rho_and_gamma(&rho, &gamma))
					{
						free_matrix(a, n);
						free_matrix(b, p);
						error = INPUT_ERROR;
					}
					else
					{
						int z = k > s ? k : s;
						a = add_by_number(a, &n, &m, z);
						if (!a)
						{
							free_matrix(b, p);
							error = ALLOCATE_ERROR;
						}
						else
						{
							b = add_by_number(b, &p, &q, z);
							if (!b)
							{
								free_matrix(a, n);
								error = ALLOCATE_ERROR;
							}
							else
							{
								/*output(a, n, m);
								printf("----\n");
								output(b, p, q);*/
								if (!rho && n == m)
									identity_matrix(a, n, m);
								else if (rho)
								{
									int **temp = allocate_matrix(n, m);
									if (!temp)
									{
										free_matrix(a, n);
										free_matrix(b, p);
										error = ALLOCATE_ERROR;
									}
									else
									{
										copying(a, temp, n, m);
										for (int i = 0; i < rho - 1; i++)
										{
											int **result = multiplication(a, n, m, temp, n, m);
											if (!result)
											{
												free_matrix(b, p);
												error = ALLOCATE_ERROR;
												break;
											}
											else
											{
												copying(result, a, n, m);
												free_matrix(result, n);
											}
										}
									}
									free_matrix(temp, n);
								}
								else if (!rho)
								{
									free_matrix(a, n);
									free_matrix(b, p);
									error = INPUT_ERROR;
								}
								else
								{
									if (!gamma && p == q)
										identity_matrix(b, p, q);
									else if (gamma)
									{
										int **temp = allocate_matrix(p, q);
										if (!temp)
										{
											free_matrix(a, n);
											free_matrix(b, p);
											error = ALLOCATE_ERROR;
										}
										else
										{
											copying(b, temp, p, q);
											for (int i = 0; i < gamma - 1; i++)
											{
												int **result = multiplication(b, p, q, temp, p, q);
												if (!result)
												{
													free_matrix(a, n);
													error = ALLOCATE_ERROR;
													break;
												}
												copying(result, b, p, q);
												free_matrix(result, p);
											}
										}
										free_matrix(temp, p);
									}
									else if (!gamma)
									{
										free_matrix(a, n);
										free_matrix(b, p);
										error = INPUT_ERROR;
									}
									if (a && b)
									{
										int **result = multiplication(a, n, m, b, p, q);
										if (!result)
											error = ALLOCATE_ERROR;
										else
										{
											output(result, n, q);
											free_matrix(a, n);
											free_matrix(b, p);
											free_matrix(result, n);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return error;
}

void identity_matrix(int **matrix, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
}

void copying(int **matrix1, int **matrix2, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix2[i][j] = matrix1[i][j];
}