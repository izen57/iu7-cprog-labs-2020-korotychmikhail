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

node_t *city_add_end(node_t *head, node_t *city)
{
	if (!head)
		return city;
	node_t *current = head;
	for (; current->next; current = current->next);
	current->next = city;
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
	if (head && *head && element && element->data)
	{
		int flag = 0;
		for (node_t *current = *head; current->next; current = current->next)
		{
			/*if (comparator(element->data, current->data) < 0 && current == *head)
			{
				flag = 1;
				element->next = current;
				node_t *before_head = *head;
				*head = element;
				free(before_head);
			}
			else*/ if (comparator(element->data, current->data) > 0 && comparator(element->data, current->next->data) < 0)
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
			for (; current->next; current = current->next);
			if (comparator(element->data, current->data) > 0)
			{
				flag = 1;
				current->next = element;
			}
			else if (!flag)
			{
				current = *head;
				if (comparator(element->data, current->data) < 0)
				{
					element->next = current;
					node_t *before_head = *head;
					*head = element;
					free(before_head);
				}
				else if (comparator(element->data, current->data) > 0)
					current->next = element;
			}
		}
	}
}

int main(/*int argc, char **argv*/void)
{
	node_t *head = NULL;
	int error = SUCCESS;
	FILE *file_in = fopen(/*argv[1]*/"D:\\c\\iu7-cprog-labs-2020-korotychmikhail\\lab_10_01_01\\in.txt", "r");
	if (file_in)
	{
		if (read_file(file_in, &head))
		{
			list_free_all(head);
			error = INPUT_ERROR;
		}
		char *string = input(stdin);
		if (!string)
		{
			list_free_all(head);
			error = INPUT_ERROR;
		}
		node_t *result = NULL;
		if (!error)
			result = find(head->next, string, comparator);
		if (!result)
		{
			list_free_all(head);
			error = NO_RESULT;
		}
		else if (!error)
		{
			void *data = pop_front(&head);
			FILE *file_out = fopen("D:\\c\\iu7-cprog-labs-2020-korotychmikhail\\lab_10_01_01\\out.txt", "w");
			if (file_out)
			{
				node_t *new_head = NULL;
				error = copy(head, &new_head);
				fprintf(file_out, "%s", (char *) data);
				list_free_all(head);
				fclose(file_out);
			}
			else
				error = INPUT_ERROR;
		}
		free(string);
		fclose(file_in);
	}
	else
		error = INPUT_ERROR;
	return error;
}