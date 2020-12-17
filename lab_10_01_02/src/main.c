#include <string.h>

#include "../inc/inout.h"
#include "../inc/list.h"

int main(void)
{
	int error = 0;
	char word[3];
	scanf("%3s", word);
	if (!error)
	{
		struct node *head1 = NULL, *head2 = NULL;
		float a = 0;
		error = input(&head1, &head2, word, &a);
		if (!error)
		{
			if (!strcmp(word, "val"))
				printf("%f", val(head1, a));
			else if (!strcmp(word, "ddx"))
			{
				struct node *head_derivative = NULL;
				dpdx(head1, &head_derivative);
				struct_print(head_derivative);
				list_free_all(head_derivative);
			}
			else if (!strcmp(word, "sum"))
			{
				struct node *head_result = NULL;
				head_result = sum(head1, head2, &head_result);
				struct_print(head_result);
				list_free_all(head_result);
			}
			else if (!strcmp(word, "dvd"))
			{
				struct node *odd_head = NULL, *even_head = NULL;
				dvd(head1, &even_head, &odd_head);
				if (!odd_head || !even_head)
					error = 1;
				if (!error)
				{
					struct_print(even_head);
					printf("\n");
					struct_print(odd_head);
					list_free_all(odd_head);
					list_free_all(even_head);
				}
			}
		}
		list_free_all(head1);
		list_free_all(head2);
	}
	return error;
}