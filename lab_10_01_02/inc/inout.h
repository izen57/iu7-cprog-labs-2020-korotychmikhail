#ifndef __INOUT_H__
#define __INOUT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

void struct_print(struct node *head);
int input(struct node **head1, struct node **head2, char *word, float *a);

#endif