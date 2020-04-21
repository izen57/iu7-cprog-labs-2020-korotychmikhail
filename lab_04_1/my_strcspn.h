#ifndef __MY__STRCSPN__H__
#define __MY__STRCSPN__H__
#define LINE_LENGHT 256
typedef enum
{
	success,
	incorrect_input,
} status_code;
void my_strcspn(char a[LINE_LENGHT + 1], char b[LINE_LENGHT + 1]);
#endif