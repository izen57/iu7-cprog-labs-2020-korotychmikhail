#include "../inc/inout.h"
#include "../inc/list.h"

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

void cities_print(node_t *head)
{
	for (node_t *temp = head; temp; temp = temp->next)
		printf("%s\n", (char *) temp->data);
}