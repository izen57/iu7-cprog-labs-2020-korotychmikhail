#include "../inc/my_snprintf.h"

void char_specifier(char *stream, size_t n, int *lenght, char symbol)
{
	if (*lenght < n - 1)
		stream[*lenght] = symbol;
	else if (*lenght < n)
		stream[*lenght] = '\0';
	(*lenght)++;
}
void integer_specifier(char *stream, size_t n, int *lenght, int symbol)
{
	unsigned int buffer;
	if (symbol < 0)
	{
		char_specifier(stream, n, lenght, '-');
		buffer = -(unsigned int) symbol;
	}
	else 
		buffer = symbol;
	int numerals = 1;
	while (buffer / numerals > 9)
		numerals *= 10;
	while (numerals > 0)
	{
		char_specifier(stream, n, lenght, '0' + buffer / numerals % 10);
		numerals /= 10;
	}
}
void long_integer_specifier(char *stream, size_t n, int *lenght, long int symbol)
{
	unsigned long int buffer;
	if (symbol < 0)
	{
		char_specifier(stream, n, lenght, '-');
		buffer = -(unsigned long int) symbol;
	}
	else 
		buffer = symbol;
	long int numeral = 1;
	while (buffer / numeral > 9)
		numeral *= 10;
	while (numeral > 0)
	{
		char_specifier(stream, n, lenght, '0' + buffer / numeral % 10);
		numeral /= 10;
	}
}
void long_long_integer_specifier(char *stream, size_t n, int *lenght, long long int symbol)
{
	unsigned long long int buffer;
	if (symbol < 0)
	{
		char_specifier(stream, n, lenght, '-');
		buffer = -(unsigned long long int) symbol;
	}
	else 
		buffer = symbol;
	long long int numeral = 1;
	while (buffer / numeral > 9)
		numeral *= 10;
	while (numeral > 0)
	{
		char_specifier(stream, n, lenght, '0' + buffer / numeral % 10);
		numeral /= 10;
	}
}

void string_specifier(char *stream, size_t n, int *lenght, const char *symbol)
{
	while (*symbol)
		char_specifier(stream, n, lenght, *symbol++);
}

int my_snprintf(char *stream, size_t n, const char *format, ...)
{
	if (!format || !stream)
		return 0;
	va_list args;
	va_start(args, format);
	int lenght = 0;
	int /*spaces, */l_count;
	bool specifier = false;
	const char *current = format;
	for (int i = 0; current[i] != '\0'; i++)
	{
		if (specifier)
			switch (current[i])
			{
				case 'c':
					char_specifier(stream, n, &lenght, va_arg(args, int));
					specifier = false;
					break;
				case 'i':
					if (l_count > 2) 
					{
						if (lenght < n) 
							stream[lenght] = '\0';
						return -1;
					}
					if (!l_count)
						integer_specifier(stream, n, &lenght, va_arg(args, int));
					else if (l_count == 1)
						long_integer_specifier(stream, n, &lenght, va_arg(args, long int));
					else if (l_count == 2)
						long_long_integer_specifier(stream, n, &lenght, va_arg(args, long long int));
					specifier = false;
					break;
				case 's':
					string_specifier(stream, n, &lenght, va_arg(args, const char *));
					specifier = false;
					break;
				case '%':
					char_specifier(stream, n, &lenght, '%');
					specifier = false;
					break;
				/*case ' ':
					spaces++;
					char_specifier(stream, n, &lenght, ' ');
					break;*/
				case 'l':
					l_count++;
					break;
				default:
					if (lenght < n) 
						stream[lenght] = '\0';
					return -1;
			}
		else
		{
			if (current[i] == '%')
			{
				specifier = true;
				//spaces = 0;
				l_count = 0;
			}
			else
				char_specifier(stream, n, &lenght, current[i]);
		}
	}
	va_end(args);
	if (lenght < n) 
		stream[lenght] = '\0';
	return lenght;
}

// int main(void)
// {
// 	char buffer[13];
// 	int res = snprintf(buffer, 4, "te%llli", 5);
// 	printf("%s", buffer);
// 	return res;
// }