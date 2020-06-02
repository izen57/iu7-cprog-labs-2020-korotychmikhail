#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#define SUCCESS 0
#define INCORRECT_INPUT 1
#define UNKNOWN_PARAMETERS 53
#define LEN_NAME 30
#define LEN_MANUFACTURER 15
#define LEN_STRUCT 100
typedef struct
{
	char name[LEN_NAME + 2];
	char manufacturer[LEN_MANUFACTURER + 2];
	uint32_t cost;
	uint32_t amount;
} information;
int read_goods(FILE *file, information goods[LEN_STRUCT], int *n);
int sorting_goods(char *input_path, char *output_path, information goods[LEN_STRUCT], int *n);
int find_goods(char *input_path, char *substr, information goods[LEN_STRUCT], int *n);
void shift(information goods[LEN_STRUCT], int pos, int *n);
int add_good(char *input_output_file, information goods[LEN_STRUCT], int *n);
#endif