#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define INPUT_ERROR 1
#define ALLOCATE_ERROR 2

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
		city->data = **name;
		city->next = NULL;
	}
	return city;
}

node_t *list_add_end(node_t *head, node_t *pers)
{
	if (!head)
		return pers;
	node_t *current = head;
	for (; current->next; current = current->next);
	current->next = pers;
	return head;
}

int read_file(FILE *file, node_t *head, char *first_name)
{
	int error = SUCCESS;
	for (int i = 0; !feof(file); i++)
	{
		char *name = input(file);
		if (!name)
			error = INPUT_ERROR;
		if (!i && !error)
			strncpy(first_name, name, strlen(name));
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
	//node_t *after_head = *head;
	void *data = /*after_head*/(*head)->data;
	*head = (*head)->next;
	return data;
}

int main(int argc, char **argv)
{
	node_t *head = NULL;
	int error = SUCCESS;
	FILE *file = fopen(argv[1], "r");
	if (file)
	{
		char *first_name;
		error = error || read_file(file, head, first_name);
		
	}
	else
		error = INPUT_ERROR;
}