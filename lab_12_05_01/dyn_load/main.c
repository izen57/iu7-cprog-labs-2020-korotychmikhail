#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "libtask.h"

ARR_DLL int ARR_DECL create_arr(int **begin, int count);
ARR_DLL int ARR_DECL counting_elems(const int *begin, const int *end);
ARR_DLL int *ARR_DECL filling_array(const int *begin, const int *end, int *index);
ARR_DLL int ARR_DECL key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

ARR_DLL int ARR_DECL counting_numbers(FILE *file, int *n);
ARR_DLL int ARR_DECL read_array(FILE *file, int **begin, int **end);
ARR_DLL void ARR_DECL output(FILE *file, int *begin, int *end);
ARR_DLL int ARR_DECL counting(int *begin, int *end);

ARR_DLL int ARR_DECL compare(const void *i, const void *j);
ARR_DLL int ARR_DECL mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *));

typedef int (__cdecl *fn_creat_arr_t)(int **, int);
typedef int (__cdecl *fn_counting_elems_t)(const int *, const int *);
typedef int *(__cdecl *fn_filling_array_t)(const int *, const int *, int *);
typedef int (__cdecl *fn_key_t)(const int *, const int *, int **, int **);
typedef int (__cdecl *fn_counting_numbers_t)(FILE *, int *);
typedef int (__cdecl *fn_read_array_t)(FILE *, int **, int **);
typedef void (__cdecl *fn_output_t)(int *, int *);
typedef int (__cdecl *fn_compare_t)(const void *,const void *);
typedef int (__cdecl *fn_mysort_t)(void *, size_t, size_t, int (*)(const void *, const void *));

int main(int argc, char **argv)
{
	int error = SUCCESS;
	if (argc == 3 || argc == 4)
	{
		FILE *in_file = fopen(argv[1], "r");
		if (in_file)
		{
			int n = 0;
			HMODULE hlib = LoadLibrary("libtask.h");
			if (!hlib)
				return MEMORY_ERROR;
			if (!counting_numbers(in_file, &n))
			{
				rewind(in_file);
				int *arr = calloc(n, sizeof(int));
				int *end = arr;
				if (!read_array(in_file, &arr, &end))
				{
					fclose(in_file);
					int *pointer = arr, count = n, *endpointer = end;
					if (argc == 4)
					{
						int *newarr, *endnewarr = newarr;
						int another_count = counting_elems(pointer, endpointer);
						if (!another_count)
						{
							free(arr);
							error = 1;
						}
						else
						{
							create_arr(&newarr, another_count);
							if (!key(arr, end, &newarr, &endnewarr))
							{
								pointer = newarr; endpointer = endnewarr;
								count = counting(pointer, endpointer);
							}
							else
							{
								free(arr);
								error = 1;
							}
						}
					}
					if (!error)
					{
						if (mysort(pointer, count, sizeof(int), compare))
						{
							free(arr);
							if (argc == 4)
								free(pointer);
							error = 1;
						}
						else
						{
							FILE *out_file = fopen(argv[2], "w");
							if (out_file)
							{
								output(out_file, pointer, endpointer);
								fclose(out_file);
								free(arr);
								if (argc == 4)
									free(pointer);
							}
							else
							{
								free(arr);
								error = FILE_ERROR;
							}
						}
					}
				}
				else
				{
					free(arr);
					error = READ_ERROR;
				}
			}
			else
				error = READ_ERROR;
		}
		else
			error = FILE_ERROR;
	}
	else
		error = ARGS_ERROR;
	return error;
}