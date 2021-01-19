#ifndef __ARR_LIB_H__
#define __ARR_LIB_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SUCCESS 0
#define ARGS_ERROR 1
#define FILE_ERROR 2
#define READ_ERROR 3
#define MEMORY_ERROR 4
#define EMPTY_RESULT 5

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif
#define ARR_DECL __cdecl

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

#endif