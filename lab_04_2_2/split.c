#include "split.h"
int split_line(char *line, char splited_line[LINE_LENGHT / 2 + 1][WORD_LENGHT])
{
	int count_of_letters = 0, count_of_splits = 1, result = 0;
	char word[WORD_LENGHT];
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '\n' || line[i] == '\0' || line[i] == '\t' || line[i] == ',' || line[i] == ';' || line[i] == ':' || line[i] == '-' || line[i] == '.' || line[i] == '!' || line[i] == '?' || line[i] == ' ')
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
		else
		{
			word[count_of_letters] = line[i];
			count_of_splits = 0;
			count_of_letters++;
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