#include "../inc/my_snprintf.h"
#include <stdarg.h>
#include <stdio.h>



void write_char(char *s, size_t n, int *len, char val)
{
    if (*len < n - 1)
        s[*len] = val;
    else if (*len < n)
        s[*len] = '\0';
    (*len)++;
}
void perform_d(char *s, size_t n, int *len, int val)
{
    unsigned int buf;
    if (val < 0)
    {
        write_char(s, n, len, '-');
        buf = -(unsigned int)val;
    }
    else 
        buf = val;
    
    int d = 1;
    while (buf / d > 9)
        d *= 10;
    
    while (d > 0)
    {
        write_char(s, n, len, '0' + buf / d % 10);
        d /= 10;
    }
}
void perform_ld(char *s, size_t n, int *len, long val)
{
    unsigned long buf;
    if (val < 0)
    {
        write_char(s, n, len, '-');
        buf = -(unsigned long)val;
    }
    else 
        buf = val;
    
    long d = 1;
    while (buf / d > 9)
        d *= 10;
    
    while (d > 0)
    {
        write_char(s, n, len, '0' + buf / d % 10);
        d /= 10;
    }
}
void perform_lld(char *s, size_t n, int *len, long long val)
{
    unsigned long long buf;
    if (val < 0)
    {
        write_char(s, n, len, '-');
        buf = -(unsigned long long)val;
    }
    else 
        buf = val;
    
    long long d = 1;
    while (buf / d > 9)
        d *= 10;
    
    while (d > 0)
    {
        write_char(s, n, len, '0' + buf / d % 10);
        d /= 10;
    }
}
void perform_x(char *s, size_t n, int *len, unsigned int val)
{
    int offset = sizeof(val) * 8 - 4;
    while ((val & (0xfu << offset)) == 0 && offset > 0)
        offset -= 4;

    while (offset >= 0)
    {
        int c = (val >> offset) & 0xf;
        if (c < 10)
            write_char(s, n, len, '0' + c);
        else
            write_char(s, n, len, 'a' + c - 10);

        offset -= 4;
    }
}
void perform_lx(char *s, size_t n, int *len, unsigned long val)
{
    int offset = sizeof(val) * 8 - 4;
    while ((val & (0xful << offset)) == 0 && offset > 0)
        offset -= 4;

    while (offset >= 0)
    {
        long c = (val >> offset) & 0xful;
        if (c < 10)
            write_char(s, n, len, '0' + c);
        else
            write_char(s, n, len, 'a' + c - 10);

        offset -= 4;
    }
}
void perform_llx(char *s, size_t n, int *len, unsigned long long val)
{
    int offset = sizeof(val) * 8 - 4;
    while ((val & (0xfull << offset)) == 0 && offset > 0)
        offset -= 4;

    while (offset >= 0)
    {
        long long c = (val >> offset) & 0xfull;
        if (c < 10)
            write_char(s, n, len, '0' + c);
        else
            write_char(s, n, len, 'a' + c - 10);

        offset -= 4;
    }
}
void perform_o(char *s, size_t n, int *len, unsigned int val)
{
    int offset = sizeof(val) * 8 - sizeof(val) * 8 % 3;
    while ((val & (0x7u << offset)) == 0 && offset > 0)
        offset -= 3;

    while (offset >= 0)
    {
        write_char(s, n, len, '0' + ((val >> offset) & 0x7u));

        offset -= 3;
    }
}
void perform_lo(char *s, size_t n, int *len, unsigned long val)
{
    int offset = sizeof(val) * 8 - sizeof(val) * 8 % 3;
    while ((val & (0x7ul << offset)) == 0 && offset > 0)
        offset -= 3;

    while (offset >= 0)
    {
        write_char(s, n, len, '0' + ((val >> offset) & 0x7ul));

        offset -= 3;
    }
}
void perform_llo(char *s, size_t n, int *len, unsigned long long val)
{
    int offset = sizeof(val) * 8 - sizeof(val) * 8 % 3;
    while ((val & (0x7ull << offset)) == 0 && offset > 0)
        offset -= 3;

    while (offset >= 0)
    {
        write_char(s, n, len, '0' + ((val >> offset) & 0x7ull));

        offset -= 3;
    }
}
void perform_s(char *s, size_t n, int *len, const char *val)
{
    while (*val)
    {
        write_char(s, n, len, *val);
        val++;
    }
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    //va_list argst;
    //va_start(argst, format);
    //int res = vsnprintf(s, n, format, argst);
    //va_end(argst);
    //return res;

    if (!format || !s)
        return -1;


    va_list args;
    va_start(args, format);

    int len = 0;
    
    int in_spec = 0;
    int spaces;
    int l_count;
    const char *cur = format;
    while (*cur)
    {
        if (in_spec)
        {   
            switch (*cur)
            {
                case 'c':
                    write_char(s, n, &len, va_arg(args, int));
                    in_spec = 0;
                    break;
                case 'd':
                    if (l_count > 2) 
                    {
                        if (len < n) 
                            s[len] = '\0';
                        return -1;
                    }
                    while (spaces--)
                        write_char(s, n, &len, ' ');
                    if (l_count == 0)
                        perform_d(s, n, &len, va_arg(args, int));
                    else if (l_count == 1)
                        perform_ld(s, n, &len, va_arg(args, long));
                    else if (l_count == 2)
                        perform_lld(s, n, &len, va_arg(args, long long));
                    in_spec = 0;
                    break;
                case 'i':
                    if (l_count > 2) 
                    {
                        if (len < n) 
                            s[len] = '\0';
                        return -1;
                    }
                    if (l_count == 0)
                        perform_d(s, n, &len, va_arg(args, int));
                    else if (l_count == 1)
                        perform_ld(s, n, &len, va_arg(args, long));
                    else if (l_count == 2)
                        perform_lld(s, n, &len, va_arg(args, long long));
                    in_spec = 0;
                    break;
                case 'x':
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
                    break;
                case 'o':
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
                    break;
                case 's':
                    perform_s(s, n, &len, va_arg(args, const char *));
                    in_spec = 0;
                    break;
                case '%':
                    write_char(s, n, &len, '%');
                    in_spec = 0;
                    break;
                case ' ':
                    spaces++;
                    //write_char(s, n, &len, ' ');
                    break;
                case 'l':
                    l_count++;
                    //write_char(s, n, &len, ' ');
                    break;
                default:
                    if (len < n) 
                        s[len] = '\0';
                    return -1;
            }
        }
        else 
        {
            if (*cur == '%')
            {
                in_spec = 1;
                spaces = 0;
                l_count = 0;
            }
            else
                write_char(s, n, &len, *cur);
        }
        cur++;
    }

    va_end(args);
    if (len < n) 
        s[len] = '\0';
    if (in_spec)
        return -1;
    else
        return len;       
}