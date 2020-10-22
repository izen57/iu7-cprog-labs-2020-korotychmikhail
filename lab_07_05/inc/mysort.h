#ifndef __MYSORT_H__
#define __MYSORT_H__
#include <stdlib.h>
int compare(const void *i, const void *j);
int mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *));
#endif