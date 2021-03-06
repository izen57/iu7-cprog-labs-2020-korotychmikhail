#include "../inc/list.h"

void list_free_all(struct node *head)
{
	for (struct node *next; head; head = next)
	{
		next = head->next;
		free(head);
	}
}

struct node *node_create(int coefficient, int degree)
{
	struct node *member = malloc(sizeof(struct node));
	if (member)
	{
		member->coefficient = coefficient;
		member->degree = degree;
		member->next = NULL;
	}
	return member;
}

struct node *node_add_end(struct node *head, struct node *node)
{
	if (!head)
		return node;
	struct node *current = head;
	for (; current->next; current = current->next);
	current->next = node;
	return head;
}

float val(struct node *head, int a)
{
	float val = 0;
	for (struct node *current = head; current; current = current->next)
		val += current->coefficient * pow(a, current->degree);
	return val;
}

void dpdx(struct node *main_head, struct node **derivative_head)
{
	for (struct node *current = main_head; current; current = current->next)
	{
		struct node *derivative_current = node_create(current->coefficient * current->degree, current->degree ? current->degree - 1 : 0);
		*derivative_head = node_add_end(*derivative_head, derivative_current);
	}
}

struct node *sum(struct node *head1, struct node *head2, struct node **result_head)
{
	if (!head1 && head2)
		*result_head = NULL;
	else
	{
		struct node *current1 = head1;
		struct node *current2 = head2;
		while (current1 || current2)
		{
			if (!current1)
			{
				struct node *result_current = node_create(current2->coefficient, current2->degree);
				*result_head = node_add_end(*result_head, result_current);
			}
			else if (!current2)
			{
				struct node *result_current = node_create(current1->coefficient, current1->degree);
				*result_head = node_add_end(*result_head, result_current);
			}
			else if (current1->degree == current2->degree)
			{
				if (current1->coefficient + current2->coefficient)
				{
					struct node *result_current = node_create(current1->coefficient + current2->coefficient, current1->degree);
					*result_head = node_add_end(*result_head, result_current);
				}
				current1 = current1->next;
				current2 = current2->next;
			}
			else if (current1->degree > current2->degree)
			{
				struct node *result_current = node_create(current1->coefficient, current1->degree);
				*result_head = node_add_end(*result_head, result_current);
				current1 = current1->next;
			}
			else if (current1->degree < current2->degree)
			{
				struct node *result_current = node_create(current2->coefficient, current2->degree);
				*result_head = node_add_end(*result_head ,result_current);
				current2 = current2->next;
			}
		}
	}
	return *result_head;
}

void dvd(struct node *head, struct node **even_head, struct node **odd_head)
{
	for (struct node *current = head; current; current = current->next)
	{
		if (current->degree % 2)
		{
			struct node *odd_current = node_create(current->coefficient, current->degree);
			*odd_head = node_add_end(*odd_head, odd_current);
		}
		else
		{
			struct node *even_current = node_create(current->coefficient, current->degree);
			*even_head = node_add_end(*even_head, even_current);
		}
	}
}