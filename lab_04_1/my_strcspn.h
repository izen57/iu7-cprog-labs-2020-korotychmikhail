#ifndef __MY__STRCSPN__H__
#define __MY__STRCSPN__H__
typedef enum
{
	success,
	incorrect_input,
	unsuitable_condition
} status_code;
#define LINE_LENGHT 256
void my_strcspn(char a[LINE_LENGHT + 1], char b[LINE_LENGHT + 1]);
#endif