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

int create_arr(int **begin, int count);
int counting_elems(const int *begin, const int *end);
int * filling_array(const int *begin, const int *end, int *index);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

int counting_numbers(FILE *file, int *n);
int read_array(FILE *file, int **begin, int **end);
void output(FILE *file, int *begin, int *end);
int counting(int *begin, int *end);

int compare(const void *i, const void *j);
int mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *));

#endif