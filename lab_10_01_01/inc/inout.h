#ifndef __INOUT_H__
#define __INOUT_H__

#include <stdio.h>
#include <stdlib.h>
#include "../inc/error_codes.h"
#include "../inc/structure.h"

char *input(FILE *file);
int read_file(FILE *file, node_t **head);
void cities_print(node_t *head);

#endif