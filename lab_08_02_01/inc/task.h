#ifndef __TASK_H__
#define __TASK_H__
void free_matrix(int **matrix, int str);
int **allocate_matrix(int str, int stb);
void remove_str_shift(int **matrix, int str, int stb, int point);
int **remove_str(int **matrix, int *str, int stb);
void remove_stb_shift(int **matrix, int str, int stb, int point);
int **remove_stb(int **matrix, int str, int *stb);
int **remove_by_number(int **matrix, int *rows, int *cols, int number);
int counting_low_average(int **matrix, int str, int stb);
int counting_minimum(int **matrix, int str, int stb);
int **add_by_number(int **matrix, int *rows, int *cols, int number);
int **add_str_and_stb(int **matrix, int *str, int *stb);
int **multiplication(int **matrix1, int str1, int stb1, int **matrix2, int str2, int stb2);
#endif