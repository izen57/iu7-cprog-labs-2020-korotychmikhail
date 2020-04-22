#define __USE_MINGW_ANSI_STDIO 1
#include <string.h>
#include <stdlib.h>
#include "my_strcspn.h"
int main(void)
{
	if (my_strcspn("", "") != 0)
		return EXIT_FAILURE;
	if (my_strcspn(" ", "\n") != 0)
		return EXIT_FAILURE;
	if (my_strcspn(" ", "\0") != 0)
		return EXIT_FAILURE;
	if (my_strcspn("\n", "scsdcds") != 0)
		return EXIT_FAILURE;
	if (my_strcspn("\0", "sddddddv") != 0)
		return EXIT_FAILURE;
	if (my_strcspn("abcde f", " gfr") != 5)
		return EXIT_FAILURE;
	if (my_strcspn("1736", "0000") != 4)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}