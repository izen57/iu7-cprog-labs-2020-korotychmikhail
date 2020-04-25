#include <stdio.h>
#include <string.h>
#include "split.h"
status_code check_line(char *line)
{
	if (line[LINE_LENGHT] != '\0' || line[LINE_LENGHT] != '\n' || line[LINE_LENGHT] != '\r')
		return incorrect_input;
	else
	{
		line[strlen(line) - 1] = '\0';
		int count_of_letters = 0, count_of_symbols = 0, flag = 0;
		for (int i = 0; line[i] != '\0'; i++)
		{
			if (line[i] == '\n' || line[i] == '\0' || line[i] == '\t' || line[i] == ',' || line[i] == ';' || line[i] == ':' || line[i] == '-' || line[i] == '.' || line[i] == '!' || line[i] == '?' || line[i] == ' ')
				count_of_letters = 0;
			else
			{
				count_of_symbols++;
				count_of_letters++;
				if (count_of_letters > WORD_LENGHT)
				{
					flag = 1;
					break;
				}
			}
		}
		if (count_of_symbols == 0 || flag)
			return incorrect_input;
		else
			return success;
	}
}
int compare(char *a, char *b)
{
	int res = 0;
	for (int i = 0; a[i] != '\0' || b[i] != '\0'; i++)
		if (a[i] != b[i])
		{
			res = 1;
			break;
		}
	return res;
}
void print_yes(char *a)
{
	for (int i = 0; a[i]  != '\0'; i++)
		printf("%c", a[i]);
	printf(" yes\n");
}
void print_no(char *a)
{
	for (int i = 0; a[i]  != '\0'; i++)
		printf("%c", a[i]);
	printf(" no\n");
}
int main(void)
{
	char first_line[LINE_LENGHT + 1];
	fgets(first_line, LINE_LENGHT + 2, stdin);
	if (check_line(first_line))
		return check_line(first_line);
	char second_line[LINE_LENGHT + 1];
	fgets(second_line, LINE_LENGHT + 2, stdin);
	if (check_line(second_line))
		return check_line(second_line);
	char first_splited_line[LINE_LENGHT / 2 + 1][WORD_LENGHT], second_splited_line[LINE_LENGHT / 2 + 1][WORD_LENGHT];
	int count_of_words1 = split_line(first_line, first_splited_line);
	int count_of_words2 = split_line(second_line, second_splited_line);
	for (int i = 0; i < count_of_words1; i++)
		for (int j = i + 1; j < count_of_words1; j++)
		{
			if (first_splited_line[i][0] == '*')
				continue;
			if (!compare(first_splited_line[i], first_splited_line[j]))
				first_splited_line[j][0] = '*';
		}
	printf("Result:\n");
	for (int i = 0; i < count_of_words1; i++)
	{
		if (first_splited_line[i][0] == '*')
			continue;
		else
		{
			int count = 0;
			for (int j = 0; j < count_of_words2; j++)
			{
				if (!compare(first_splited_line[i], second_splited_line[j]))
				{
					print_yes(first_splited_line[i]);
					break;
				}
				else
					count++;
			}
			if (count == count_of_words2)
				print_no(first_splited_line[i]);
		}
	}
}