#include "../inc/list.h"

void list_free_all(node_t *head)
{
	node_t *next;
	for (; head; head = next)
	{
		next = head->next;
		free(head);
	}
}

node_t *city_create(char *name)
{
	node_t *city = malloc(sizeof(node_t));
	if (city)
	{
		city->data = name;
		city->next = NULL;
	}
	return city;
}

node_t *city_add_end(node_t *head, node_t *city)
{
	if (!head)
		return city;
	node_t *current = head;
	for (; current->next; current = current->next);
	current->next = city;
	return head;
}

void *pop_front(node_t **head)
{
	void *data;
	if (!head || !*head)
		data = NULL;
	else
	{
		data = (*head)->data;
		node_t *before_head = *head;
		*head = (*head)->next;
		free(before_head);
	}
	return data;
}

int comparator(const void *data1, const void *data2)
{
	int res;
	if (!data1 || !data2)
		res = 0;
	else
		res = memcmp(data1, data2, sizeof(void *));
	return res;
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
	node_t *result;
	if (!head)
		result = NULL;
	else
	{
		int flag = 0;
		for (node_t *current = head; current; current = current->next)
			if (!comparator(data, current->data))
			{
				flag = 1;
				result = current;
				break;
			}
		if (!flag)
			result = NULL;
	}
	return result;
}

int copy(node_t *head, node_t **new_head)
{
	int error = 0;
	if (!head)
		error = 1;
	else
		for (node_t *current = head; current; current = current->next)
		{
			node_t *new_current = malloc(sizeof(node_t));
			if (new_current)
			{
				new_current->data = current->data;
				new_current->next = NULL;
			}
			else
			{
				error = 1;
				break;
			}
			if (!*new_head)
				*new_head = new_current;
			else
			{
				node_t *temp = *new_head;
				for (; temp->next; temp = temp->next);
				temp->next = new_current;
			}
		}
	return error;
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
	if (head && *head && element)
	{
		int flag = 0;
		for (node_t *current = *head; current->next; current = current->next)
		{
			if (comparator(element->data, current->data) > 0 && comparator(element->data, current->next->data) < 0)
			{
				flag = 1;
				node_t *temp_next = current->next;
				current->next = element;
				element->next = temp_next;
			}
			break;
		}
		if (!flag)
		{
			node_t *current = *head;
			//for (; current->next; current = current->next);
			if (comparator(element->data, current->data) <= 0)
			{
				//flag = 1;
				//current->next = element;
				element->next = *head;
				*head = element;
			}
			else /*if (!flag)*/
			{
				//current = *head;
				/*if (comparator(element->data, current->data) < 0)
				{
					element->next = current;
					node_t *before_head = *head;
					*head = element;
					free(before_head);
				}*/
				for (; current->next; current = current->next);
				/*else*/ if (comparator(element->data, current->data) > 0)
					current->next = element;
			}
		}
	}
	else if (!*head)
	{
		*head = element;
		element->next = NULL;
	}
}