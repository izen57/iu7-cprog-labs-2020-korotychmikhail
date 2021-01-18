#ifndef __MY_SNPRINTF_H__
#define __MY_SNPRINTF_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void char_specifier(char *stream, size_t n, int *lenght, char symbol);
void integer_specifier(char *stream, size_t n, int *lenght, int symbol);
void long_integer_specifier(char *stream, size_t n, int *lenght, long int symbol);
void long_long_integer_specifier(char *stream, size_t n, int *lenght, long long int symbol);
void string_specifier(char *stream, size_t n, int *lenght, const char *symbol);
int my_snprintf(char *stream, size_t n, const char *format, ...);

#endif