#include <stdio.h>
#include <string.h>
//#include "split.h"
#define LINE_LENGHT 256
#define WORD_LENGHT 16
void del_not_first(char line[WORD_LENGHT])
{
	for (int i = 1; i < strlen(line); i++)
		if (line[i] == line[0])
			for (int j = i; j < strlen(line); j++)
				line[j] = line[j + 1];
}
void line_processing(char splited_line[LINE_LENGHT / 2 + 1][WORD_LENGHT], int count_of_words)
{
	char new_str[LINE_LENGHT / 2 + 1][WORD_LENGHT];
	for (int i = count_of_words - 2; i >= 1; i--)
		if (!strcmp(splited_line[i], splited_line[count_of_words - 1]))
			splited_line[i][0] = '*';
	int j = 0, count_of_words2 = 0;
	for (int i = count_of_words - 1; i >= 1; i--)
	{
		if (splited_line[i][0] == '*')
			continue;
		del_not_first(splited_line[i]);
		count_of_words2++;
		strcpy(new_str[j++], splited_line[i]);
	}
	for (int i = 0; i < count_of_words2; i++)
		printf("%s\n", new_str[i]);
	printf("%s", new_str[count_of_words2]);
}
int split_line(char *line, char splited_line[LINE_LENGHT / 2 + 1][WORD_LENGHT])
{
	int count_of_letters = 0, count_of_splits = 1, result = 0;
	char word[WORD_LENGHT];
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (line[i] != '\n' && line[i] != '\0' && line[i] != '\t' && line[i] != ',' && line[i] != ';' && line[i] != ':' && line[i] != '-' && line[i] != '.' && line[i] != '!' && line[i] != '?' && line[i] != ' ')
		{
			word[count_of_letters] = line[i];
			count_of_splits = 0;
			count_of_letters++;
		}
		else
		{
			if (count_of_splits == 0)
			{
				count_of_splits++;
				for (int j = 0; j < count_of_letters; j++)
				{
					splited_line[result][j] = word[j];
					word[j] = '\0';
				}
				for (int j = count_of_letters; j < WORD_LENGHT; j++)
					splited_line[result][j] = '\0';
				result++;
				count_of_letters = 0;
			}
		}
	}
	if (count_of_letters > 0)
	{
		for (int j = 0; j < count_of_letters; j++)
		{
			splited_line[result][j] = word[j];
			word[j] = '\0';
		}
		for (int j = count_of_letters; j < WORD_LENGHT; j++)
			splited_line[result][j] = '\0';
		result++;
	}
	return result;
}
/*status_code*/int check_line(char *line)
{
	if (line[LINE_LENGHT] != '\0' && line[LINE_LENGHT] != '\n' && line[LINE_LENGHT] != '\r')
		return 1/*incorrect_input*/;
	else
	{
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
			return 1/*incorrect_input*/;
		else
			return 0/*success*/;
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
	line_processing(splited_line, count_of_words);
	return 0/*success*/;
}