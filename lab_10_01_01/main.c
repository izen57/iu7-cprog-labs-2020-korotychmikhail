#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SUCCESS 0
#define INPUT_ERROR 1
#define ALLOCATE_ERROR 2
#define NO_RESULT 3

typedef struct node node_t;
struct node
{
	void *data;
	node_t *next;
};

char *input(FILE *file)
{
	int capacity = 1, size = 0;
	char *s = (char *) malloc(capacity * sizeof(char));
	for (char c = fgetc(file); c != '\n' && c != EOF; c = fgetc(file))
	{
		s[size++] = c;
		if (size >= capacity)
		{
			capacity *= 2;
			s = (char *) realloc(s, capacity * sizeof(char));
			if (!s)
				return NULL;
		}
	}
	s[size] = '\0';
	return s;
}

void cities_free(node_t *city)
{
	free(city);
}

void list_free_all(node_t *head)
{
	for (node_t *next; head; head = next)
	{
		next = head->next;
		cities_free(head);
	}
}

node_t *city_create(char **name)
{
	node_t *city = malloc(sizeof(node_t));
	if (city)
	{
		city->data = *name;
		city->next = NULL;
	}
	return city;
}

node_t *city_add_end(node_t *head, node_t *pers)
{
	if (!head)
		return pers;
	node_t *current = head;
	for (; current->next; current = current->next);
	current->next = pers;
	return head;
}

int read_file(FILE *file, node_t *head)
{
	int error = SUCCESS;
	while(!feof(file))
	{
		char *name = input(file);
		if (!name)
			error = INPUT_ERROR;
		if (!error)
		{
			node_t *node = city_create(&name);
			head = city_add_end(head, node);
		}
	}
	return error;
}

void *pop_front(node_t **head)
{
	if (!*head || !head)
		return NULL;
	node_t *after_head = *head;
	void *data = (*head)->data;
	*head = (*head)->next;
	free(after_head);
	return data;
}

int comparator(const void *data1, const void *data2)
{
	bool flag = false;
	if (!strcmp(data1, data2))
		flag = true;
	return flag;
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
	node_t *current = NULL;
	for (current = head->next; current->next; current = current->next)
		if (comparator(data, current->data))
			break;
	return current;
}

int main(int argc, char **argv)
{
	node_t *head = NULL;
	int error = SUCCESS;
	FILE *file = fopen(argv[1], "r");
	if (file)
	{
		error = error || read_file(file, head);
		node_t *result = find(head, head->data, comparator);
		if (!result)
			error = NO_RESULT;
		else
			printf("%s", (char *) result->data);
		list_free_all(head);
	}
	else
		error = INPUT_ERROR;
	return error;
}