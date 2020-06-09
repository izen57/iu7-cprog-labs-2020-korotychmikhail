//прочитать список структур в массив, вывести на экран. Самый старый город
#include <stdio.h>
#include <string.h>
typedef struct
{
	char name[100 + 1];
	int year;
	int population;
} information;
void zeroing(information *cities)
{
	for (int i = 0; i < 1300; i++)
		for (int j = 0; j <= 100 + 1; j++)
			cities[i].name[j] = '\0';
}
int read_file(FILE *file, information *cities, int *count)
{
	for (int i = 0; !feof(file); i++)
	{
		if (!fgets(cities[i].name, 100 + 1, file))
			return 1;
		(*count)++;
		for (int j = 0; j < 100 + 1; j++)
			if (cities[i].name[j] == '\n')
			{
				cities[i].name[j] = '\0';
				break;
			}
		if (fscanf(file, "%d\n", &cities[i].year) != 1)
			return 1;
		(*count)++;
		if (fscanf(file, "%d\n", &cities[i].population) != 1)
			return 1;
		(*count)++;
	}
	if (*count % 3)
		return 1;
	else
		*count /= 3;
	return 0;
}
information old_city(information *cities, int count)
{
	information old_city = cities[0];
	int maxyear = cities[0].year;
	for (int i = 1; i < count; i++)
		if (cities[i].year > maxyear)
		{
			maxyear = cities[i].year;
			old_city = cities[i];
		}
	return old_city;
}
void print_res(FILE *file, information result)
{
	fprintf(file, "%s\n%d\n%d\n", result.name, result.year, result.population);
}
int process(FILE *fin, FILE *fout)
{

	int count = 0;
	information cities[1300];
	zeroing(cities);
	if (read_file(fin, cities, &count))
		return 1;
	information result = old_city(cities, count);
	print_res(fout, result);
	return 0;
}
int main(void)
{
	FILE *fin = fopen("D:\\2sem\\C\\iu7-cprog-labs-2020-korotychmikhail\\rk_02A\\in.txt", "r");
	FILE *fout = fopen("D:\\2sem\\C\\iu7-cprog-labs-2020-korotychmikhail\\rk_02A\\out.txt", "w");
	int error = process(fin/*stdin*/, fout/*stdout*/);
	fclose(fin);
	fclose(fout);
	return error;
}