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
	char *s = malloc(capacity * sizeof(char));
	for (char c = fgetc(file); c != '\n' && c != EOF; c = fgetc(file))
	{
		s[size++] = c;
		if (size >= capacity)
		{
			capacity *= 2;
			s = realloc(s, capacity * sizeof(char));
			if (!s)
				return NULL;
		}
	}
	s[size] = '\0';
	return s;
}

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

node_t *city_add_end(node_t *head, node_t *cities)
{
	if (!head)
		return cities;
	node_t *current = head;
	for (; current->next; current = current->next);
	current->next = cities;
	return head;
}

void cities_print(node_t *head)
{
	for (node_t *temp = head; temp; temp = temp->next)
		printf("%s\n", (char *) temp->data);
}

int read_file(FILE *file, node_t **head)
{
	int error = SUCCESS;
	while (!feof(file))
	{
		char *name = input(file);
		if (!name)
		{
			error = INPUT_ERROR;
			break;
		}
		if (!error)
		{
			node_t *node = city_create(name);
			*head = city_add_end(*head, node);
		}
	}
	return error;
}

void *pop_front(node_t **head)
{
	if (!*head || !head)
		return NULL;
	void *data = (*head)->data;
	*head = (*head)->next;
	return data;
}

int comparator(const void *data1, const void *data2)
{
	int flag = 0;
	if (!memcmp(data1, data2, sizeof(void *)))
		flag = 1;
	return flag;
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
	int flag = 0;
	node_t *result;
	for (node_t *current = head->next; current; current = current->next)
		if (comparator(data, current->data))
		{
			flag = 1;
			result = current;
			break;
		}
	if (!flag)
	{
		list_free_all(head);
		result = NULL;
	}
	return result;
}

int main(/*int argc, char **argv*/void)
{
	node_t *head = NULL;
	int error = SUCCESS;
	FILE *file = fopen(/*argv[1]*/"D:\\c\\iu7-cprog-labs-2020-korotychmikhail\\lab_10_01_01\\in.txt", "r");
	if (file)
	{
		if (read_file(file, &head))
		{
			list_free_all(head);
			error = INPUT_ERROR;
		}
		node_t *result;
		if (!error)
			result = find(head, head->data, comparator);
		if (!result)
			error = NO_RESULT;
		else
		{
			result = pop_front(&head);
			printf("%s", (char *) result->data);
			list_free_all(head);
			fclose(file);
		}
	}
	else
		error = INPUT_ERROR;
	return error;
}