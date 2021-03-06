#include <stdio.h>
#include <string.h>
#include "split.h"
void del_not_first(char line[WORD_LENGHT])
{
	int count = 0;
	for (int i = 0; i <= strlen(line); i++)
		count++;
	for (int i = 1; i < count; i++)
		if (line[i] == line[0])
		{
			for (int j = i; j < count; j++)
				line[j] = line[j + 1];
			count--;
			i--;
		}
}
status_code line_processing(char splited_line[LINE_LENGHT / 2 + 1][WORD_LENGHT], int count_of_words)
{
	char new_str[LINE_LENGHT / 2 + 1][WORD_LENGHT];
	int count_of_words3 = 1;
	for (int i = count_of_words - 2; i >= 0; i--)
		if (!strcmp(splited_line[i], splited_line[count_of_words - 1]))
		{
			count_of_words3++;
			splited_line[i][0] = '*';
		}
	if (count_of_words3 == count_of_words)
		return incorrect_input;
	int j = 0, count_of_words2 = 0;
	for (int i = count_of_words - 2; i >= 0; i--)
	{
		if (splited_line[i][0] == '*')
			continue;
		del_not_first(splited_line[i]);
		strcpy(new_str[j++], splited_line[i]);
		count_of_words2++;
	}
	printf("Result: ");
	for (int i = 0; i < count_of_words2 - 1; i++)
		printf("%s ", new_str[i]);
	printf("%s\n", new_str[count_of_words2 - 1]);
	return success;
}
status_code check_line(char *line)
{
	if (line[LINE_LENGHT] != '\0' && line[LINE_LENGHT] != '\n' && line[LINE_LENGHT] != EOF)
		return incorrect_input;
	else
	{
		if (line[LINE_LENGHT + 1] == '\n')
			line[strlen(line) - 1] = '\0';
		int count_of_letters = 0, count_of_symbols = 0, flag = 0;
		for (int i = 0; line[i] != '\0'; i++)
		{
			if (line[i] != '\n' && line[i] != '\0' && line[i] != '\t' && line[i] != '\r' && line[i] != ',' && line[i] != ';' && line[i] != ':' && line[i] != '-' && line[i] != '.' && line[i] != '!' && line[i] != '?' && line[i] != ' ')
			{
				count_of_symbols++;
				count_of_letters++;
				if (count_of_letters > WORD_LENGHT)
				{
					flag = 1;
					break;
				}
			}
			else
				count_of_letters = 0;
		}
		if (count_of_symbols == 0 || flag)
			return incorrect_input;
		else
			return success;
	}
}
int main(void)
{
	char line[LINE_LENGHT + 2];
	for (int i = 0; i < LINE_LENGHT + 2; i++)
		line[i] = '\0';
	fgets(line, LINE_LENGHT + 2, stdin);
	if (check_line(line))
		return check_line(line);
	char splited_line[LINE_LENGHT / 2 + 1][WORD_LENGHT];
	int count_of_words = split_line(line, splited_line);
	if (count_of_words <= 1)
		return incorrect_input;
	if (line_processing(splited_line, count_of_words))
		return incorrect_input;
	return success;
}