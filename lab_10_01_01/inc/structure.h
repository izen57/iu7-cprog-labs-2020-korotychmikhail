#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

typedef struct node node_t;
struct node
{
	void *data;
	node_t *next;
};

#endif