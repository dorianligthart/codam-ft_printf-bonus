#include "libft.h"
#include <stddef.h>
#include <stdarg.h>

int ft_printf(const char *format, ...)
{
    va_list ap;
    int     tmp;

    va_start(ap, format);
    tmp = ft_vprintf(format, ap);
    va_end(ap);
    return (tmp);
}

// int ft_fprintf(FILE *stream, const char *format, ...)
// {
//     va_list ap;
//     int     tmp;

//     va_start(ap, format);
//     tmp = ft_vfprintf(stream, format, ap);
//     va_end(ap);
//     return (tmp);
// }

int ft_sprintf(char *str, const char *format, ...)
{
    va_list ap;
    int     tmp;

    va_start(ap, format);
    tmp = ft_vsprintf(str, format, ap);
    va_end(ap);
    return (tmp);
}

int ft_snprintf(char *str, size_t size, const char *format, ...)
{
    va_list ap;
    int     tmp;

    va_start(ap, format);
    tmp = ft_snprintf(str, size, format, ap);
    va_end(ap);
    return (tmp);
}

int ft_dprintf(int fd, const char *format, ...)
{
    va_list ap;
    int     tmp;

    va_start(ap, format);
    tmp = ft_vdprintf(fd, format, ap);
    va_end(ap);
    return (tmp);
}

