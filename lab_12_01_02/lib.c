#include "lib.h"

ARR_DLL void ARR_DECL shift(int *a, int n, int k)
{
	if (!a || n <= 0 || k <= 0)
		return;
	for (int i = 0; i < k; i++)
	{
		int temp = a[0];
		for (int j = 0; j < n - 1; j++)
			a[j] = a[j + 1];
		a[n - 1] = temp;
	}
}

ARR_DLL void ARR_DECL square_numbers(int *a, int n, int *b)
{
	for (int i = 0, j = 0; i < n; i++)
		if (a[i] == pow(round(sqrt(a[i])), 2))
			b[j++] = a[i];
}