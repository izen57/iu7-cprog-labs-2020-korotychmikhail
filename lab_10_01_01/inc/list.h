#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <string.h>
#include "structure.h"

void list_free_all(node_t *head);
node_t *city_create(char *name);
node_t *city_add_end(node_t *head, node_t *city);
void *pop_front(node_t **head);
int comparator(const void *data1, const void *data2);
node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));
int copy(node_t *head, node_t **new_head);
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));

#endif