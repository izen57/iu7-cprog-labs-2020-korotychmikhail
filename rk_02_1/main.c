#include <stdio.h>
typedef struct
{
	char name[100 + 1];
	int year;
	int population;
} information;
int read_file(FILE *fin, information cities[1300], int *count)
{
	for (int i = 0; !feof(fin); i++)
	{
		fgets(cities[i].name, 100 + 1, fin);
		(*count)++;
		for (int j = 0; j < 100 + 1; j++)
			if (cities[i].name[j] == '\n')
				cities[i].name[j] = '\0';
		fscanf(fin, "%d\n", &cities[i].year);
		(*count)++;
		fscanf(fin, "%d\n", &cities[i].population);
		(*count)++;
	}
	if (*count % 3)
		return 1;
	return 0;
}
int sort_file(information cities[1300], int count)
{
	information temp;
	int flag;
	do
	{
		flag = 0;
		for (int i = 0; i < count - 1; i++)
			if (cities[i].population < cities[i + 1].population)
			{
				temp = cities[i];
				cities[i] = cities[i + 1];
				cities[i + 1] = temp;
				flag = 1;
			}
	}
	while (flag);
	return 0;
}
void print_file(FILE *fout, FILE *fin, information cities[1300])
{
	for (int i = 0; i < 5 || !feof(fin); i++)
		fprintf(fout, "%s\n", cities[i].name);
}
int process(FILE *fin, FILE *fout)
{
	information cities[1300];
	for (int i = 0; !feof(fin); i++)
		for (int j = 0; j <= 100 + 1; j++)
			cities[i].name[j] = '\0';
	int count = 0;
	if (read_file(fin, cities, &count))
		return 1;
	if (sort_file(cities, count))
		return 1;
	print_file(fout, fin, cities);
	return 0;
}
int main(void)
{
	FILE *fin = fopen("in.txt", "r");
	if (!fin)
		return 1;
	FILE *fout = fopen("out.txt", "w");
	int error =  process(fin, fout);
	fclose(fin);
	fclose(fout);
	return error;
}