#include "../inc/my_snprintf.h"

void char_specifier(char *stream, size_t n, int *lenght, char symbol)
{
	if (*lenght < n - 1)
		stream[(*lenght)++] = symbol;
	else if (*lenght < n)
		stream[(*lenght)++] = '\0';
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
// void perform_x(char *s, size_t n, int *len, unsigned int val)
// {
// 	int offset = sizeof(val) * 8 - 4;
// 	while ((val & (0xfu << offset)) == 0 && offset > 0)
// 		offset -= 4;

// 	while (offset >= 0)
// 	{
// 		int c = (val >> offset) & 0xf;
// 		if (c < 10)
// 			write_char(s, n, len, '0' + c);
// 		else
// 			write_char(s, n, len, 'a' + c - 10);

// 		offset -= 4;
// 	}
// }
// void perform_lx(char *s, size_t n, int *len, unsigned long val)
// {
// 	int offset = sizeof(val) * 8 - 4;
// 	while ((val & (0xful << offset)) == 0 && offset > 0)
// 		offset -= 4;

// 	while (offset >= 0)
// 	{
// 		long c = (val >> offset) & 0xful;
// 		if (c < 10)
// 			write_char(s, n, len, '0' + c);
// 		else
// 			write_char(s, n, len, 'a' + c - 10);

// 		offset -= 4;
// 	}
// }
// void perform_llx(char *s, size_t n, int *len, unsigned long long val)
// {
// 	int offset = sizeof(val) * 8 - 4;
// 	while ((val & (0xfull << offset)) == 0 && offset > 0)
// 		offset -= 4;

// 	while (offset >= 0)
// 	{
// 		long long c = (val >> offset) & 0xfull;
// 		if (c < 10)
// 			write_char(s, n, len, '0' + c);
// 		else
// 			write_char(s, n, len, 'a' + c - 10);

// 		offset -= 4;
// 	}
// }
// void perform_o(char *s, size_t n, int *len, unsigned int val)
// {
// 	int offset = sizeof(val) * 8 - sizeof(val) * 8 % 3;
// 	while ((val & (0x7u << offset)) == 0 && offset > 0)
// 		offset -= 3;

// 	while (offset >= 0)
// 	{
// 		write_char(s, n, len, '0' + ((val >> offset) & 0x7u));

// 		offset -= 3;
// 	}
// }
// void perform_lo(char *s, size_t n, int *len, unsigned long val)
// {
// 	int offset = sizeof(val) * 8 - sizeof(val) * 8 % 3;
// 	while ((val & (0x7ul << offset)) == 0 && offset > 0)
// 		offset -= 3;

// 	while (offset >= 0)
// 	{
// 		write_char(s, n, len, '0' + ((val >> offset) & 0x7ul));

// 		offset -= 3;
// 	}
// }
// void perform_llo(char *s, size_t n, int *len, unsigned long long val)
// {
// 	int offset = sizeof(val) * 8 - sizeof(val) * 8 % 3;
// 	while ((val & (0x7ull << offset)) == 0 && offset > 0)
// 		offset -= 3;

// 	while (offset >= 0)
// 	{
// 		write_char(s, n, len, '0' + ((val >> offset) & 0x7ull));

// 		offset -= 3;
// 	}
// }
void string_specifier(char *stream, size_t n, int *lenght, const char *symbol)
{
	while (*symbol)
		char_specifier(stream, n, lenght, *symbol++);
}

int my_snprintf(char *stream, size_t n, const char *format, ...)
{
	if (!format || !stream)
		return -1;
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
				/*case 'd':
					if (l_count > 2) 
					{
						if (lenght < n) 
							stream[lenght] = '\0';
						return -1;
					}
					while (spaces--)
						write_char(stream, n, &lenght, ' ');
					if (l_count == 0)
						perform_d(s, n, &len, va_arg(args, int));
					else if (l_count == 1)
						perform_ld(s, n, &len, va_arg(args, long));
					else if (l_count == 2)
						perform_lld(s, n, &len, va_arg(args, long long));
					in_spec = 0;
					break;*/
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
				/*case 'x':
					if (l_count > 2) 
					{
						if (len < n) 
							s[len] = '\0';
						return -1;
					}
					if (l_count == 0)
						perform_x(s, n, &len, va_arg(args, unsigned int));
					else if (l_count == 1)
						perform_lx(s, n, &len, va_arg(args, unsigned long));
					else if (l_count == 2)
						perform_llx(s, n, &len, va_arg(args, unsigned long long));
					in_spec = 0;
					break;*/
				/*case 'o':
					if (l_count > 2) 
					{
						if (len < n) 
							s[len] = '\0';
						return -1;
					}
					if (l_count == 0)
						perform_o(s, n, &len, va_arg(args, unsigned int));
					else if (l_count == 1)
						perform_lo(s, n, &len, va_arg(args, unsigned long));
					else if (l_count == 2)
						perform_llo(s, n, &len, va_arg(args, unsigned long long));
					in_spec = 0;
					break;*/
				case 's':
					string_specifier(stream, n, &lenght, va_arg(args, const char *));
					specifier = false;
					break;
				/*case '%':
					write_char(s, n, &len, '%');
					in_spec = 0;
					break;*/
				/*case ' ':
					spaces++;
					//write_char(s, n, &len, ' ');
					break;*/
				case 'l':
					l_count++;
					//write_char(s, n, &len, ' ');
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
	if (specifier)
		return -1;
	else
		return lenght;
}

/*int main(void)
{
	char buffer[13];
	return my_snprintf(buffer, 13, "I'm coding now...");
}*/