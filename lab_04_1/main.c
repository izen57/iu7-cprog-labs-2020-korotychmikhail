#include <stdlib.h>
#include "my_strcspn.h"
int main(void)
{
	if (my_strcspn("", "") != 0)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}