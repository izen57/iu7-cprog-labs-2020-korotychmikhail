#ifndef __SORT_NUMBERS_H__
#define __SORT_NUMBERS_H__
#define SUCCESS 0
#define INCORRECT_INPUT 1
int get_number_by_pos(FILE *file, int pos);
void put_number_by_pos(FILE *file, int *num, int pos);
int sort_numbers(char *path);
#endif