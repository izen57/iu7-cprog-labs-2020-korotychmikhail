#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structure.h"
#include "list.h"
#include "error_codes.h"
#include "inout.h"

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