#include "libft.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

//printf()'s va_list function.
int ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}

// //fprintf()'s va_list function.
// int ft_vfprintf(FILE *stream, const char *format, va_list ap)
// {
//     return (42);
// }

//sprintf()'s va_list function.
int ft_vsprintf(char *str, const char *format, va_list ap)
{
	size_t  result;

	result = (size_t)ft_vsnprintf(NULL, 0, format, ap);
	return (ft_vsnprintf(str, result, format, ap));
}

//snprintf()'s va_list function.
int ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	t_pfstruct  p;

	p.str = str;
	p.size = size;
	va_copy(p.ap, ap);
	p.format = format;
	p.bytes = 0;
	while (*p.format)
	{
		if (*p.format == '%')
			ft_vsnprintf_new_conv(&p);
		else
		{
			while (*p.format && *p.format != '%')
			{
				if (str && p.bytes < size)
					str[p.bytes] = *(p.format);
				p.bytes++;
				p.format++;
			}
		}
	}
	return (p.bytes);
}

//dprintf()'s va_list function.
int ft_vdprintf(int fd, const char *format, va_list ap)
{
	char	*str;
	size_t	result;
	int		tmp;

	result = (size_t)ft_vsnprintf(NULL, 0, format, ap);
	str = (char *)malloc(result * sizeof(char));
	if (!str)
		return (PF_ERROR);
	ft_vsprintf(str, format, ap);
	tmp = write(fd, str, result);
	free(str);
	return (tmp);
}

