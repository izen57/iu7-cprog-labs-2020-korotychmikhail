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
	int flag = 0;
	if (!data1 || !data2)
		flag = 0;
	else
	{
		data1 = (const char *) data1;
		data2 = (const char *) data2;
		if (!strcmp(data1, data2))
			flag = 1;
	}
	return flag;
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
			if (comparator(data, current->data))
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
			error = INPUT_ERROR;
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