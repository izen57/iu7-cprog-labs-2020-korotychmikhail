#include "../inc/inout.h"
#include "../inc/list.h"

void struct_print(struct node *head)
{
	for (struct node *current = head; current; current = current->next)
		printf("%d %d ", current->coefficient, current->degree);
	printf("L");
}

char *read(FILE *file)
{
	int capacity = 1, size = 0;
	char *s = malloc(capacity * sizeof(char));
	for (char c = fgetc(file); c != '\n' && c != ' ' && c != EOF; c = fgetc(file))
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

int input(struct node **head1, struct node **head2, char *word, float *a)
{
	int error = 0;
	if (!strcmp(word, "val") || !strcmp(word, "ddx") || !strcmp(word, "sum") || !strcmp(word, "dvd"))
	{
		int coefficient, degree;
		int n = 0;
		char *c;
		while (1)
		{
			c = read(stdin);
			if (!strlen(c))
				break;
			coefficient = atoi(c);
			n++;
			c = read(stdin);
			if (!strlen(c))
				break;
			degree = atoi(c);
			n++;
			struct node *member = node_create(coefficient, degree);
			*head1 = node_add_end(*head1, member);
		}
		if (!n || n % 2)
			error = 1;
		if (!error && !strcmp(word, "val"))
		{
			if (scanf("%f", a) != 1)
				error = 1;
		}
		else if (!error && !strcmp(word, "sum"))
			while (1)
			{
				c = read(stdin);
				if (!strlen(c))
					break;
				coefficient = atoi(c);
				c = read(stdin);
				if (!strlen(c))
					break;
				degree = atoi(c);
				struct node *member = node_create(coefficient, degree);
				*head1 = node_add_end(*head1, member);
			}
	}
	else
		error = 1;
	return error;
}