#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "structure.h"

void list_free_all(struct node *head);
struct node *node_create(int coefficient, int degree);
struct node *node_add_end(struct node *head, struct node *node);
float val(struct node *head, int a);
void dPdx(struct node *main_head, struct node **derivative_head);
struct node *sum(struct node *head1, struct node *head2, struct node **result_head);
void dvd(struct node *head, struct node **even_head, struct node **odd_head);

#endif