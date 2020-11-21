#ifndef __INOUT_H__
#define __INOUT_H__
#include <stdio.h>
#include "../inc/structure.h"
void print(struct information *stuff, int n);
void free_information(struct information *stuff, int n);
char *input(FILE *file);
int counting_structures(FILE *file);
int read_stuff(FILE *file, struct information *stuff);
#endif