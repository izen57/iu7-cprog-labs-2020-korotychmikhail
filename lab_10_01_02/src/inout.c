#include "../inc/inout.h"
#include "../inc/list.h"

void struct_print(struct node *head)
{
	for (struct node *current = head; current; current = current->next)
		printf("%d %d ", current->coefficient, current->degree);
	printf("L");
}

int input(struct node **head1, struct node **head2, char *word, float *a)
{
	int error = 0;
	if (!strcmp(word, "val") || !strcmp(word, "ddx") || !strcmp(word, "sum") || !strcmp(word, "dvd"))
	{
		int coefficient, degree;
		int n = 0;
		while (1)
		{
			if (scanf("%d", &coefficient) != 1)
			{
				error = 1;
				break;
			}
			n++;
			if (getchar() == '\n')
			{
				error = 1;
				break;
			}
			if (scanf("%d", &degree) != 1)
			{
				error = 1;
				break;
			}
			n++;
			struct node *member = node_create(coefficient, degree);
			*head1 = node_add_end(*head1, member);
			if (getchar() == '\n')
				break;
		}
		if (!n || n % 2)
			error = 1;
		if (!error && !strcmp(word, "val"))
		{
			if (scanf("%f", a) != 1)
				error = 1;
		}
		else if (!error && !strcmp(word, "sum"))
		{
			while (1)
			{
				if (scanf("%d", &coefficient) != 1)
				{
					error = 1;
					break;
				}
				n++;
				if (getchar() == '\n')
				{
					error = 1;
					break;
				}
				if (scanf("%d", &degree) != 1)
				{
					error = 1;
					break;
				}
				n++;
				struct node *member = node_create(coefficient, degree);
				*head1 = node_add_end(*head1, member);
				if (getchar() == '\n')
				{
					error = 1;
					break;
				}
			}
			if (!n || n % 2)
				error = 1;
		}
	}
	else
		error = 1;
	return error;
}