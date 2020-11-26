#ifndef __KEY_H__
#define __KEY_H__

int create_arr(int **begin, int count);
int counting_elems(const int *begin, const int *end);
int *filling_array(const int *begin, const int *end, int *index);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif