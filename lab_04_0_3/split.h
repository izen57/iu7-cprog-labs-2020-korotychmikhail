#ifndef __SPLIT__H__
#define __SPLIT__H__
#define LINE_LENGHT 256
#define WORD_LENGHT 16
typedef enum
{
	success,
	incorrect_input
} status_code;
int split_line(char *line, char splited_line[LINE_LENGHT / 2 + 1][WORD_LENGHT]);
#endif