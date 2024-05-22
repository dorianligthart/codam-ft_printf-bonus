#include "printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

//printf()'s va_list function.
int ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}

//sprintf()'s va_list function.
int ft_vsprintf(char *str, const char *format, va_list ap)
{
	int  result;

	result = ft_vsnprintf(NULL, 0, format, ap);
	if (result < 0)
		return (FT_ERROR);
	return (ft_vsnprintf(str, (size_t)result + 1, format, ap));
}

//snprintf()'s va_list function.
int ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	t_pfstruct  p;

	p.str = str;
	p.size = size;
	va_copy(p.ap, ap);
	va_copy(p.oldap, ap);
	p.format = format;
	p.bytes = 0;
	while (*p.format)
	{
		if (*p.format == '%' && !ft_pf_new_conversion(&p))
			return (FT_ERROR);
		if (*p.format != '%' && p.bytes + FT_TERMINATOR < size)
		{
			str[p.bytes] = *(p.format);
			++p.format;
			++p.bytes;
		}
	}
	if (p.bytes < size)
		str[p.bytes] = '\0';
	return (p.bytes);
}

//dprintf()'s va_list function. takes filedescriptor.
int ft_vdprintf(int fd, const char *format, va_list ap)
{
	char	*str;
	int		result;

	result = ft_vsnprintf(NULL, 0, format, ap) + FT_TERMINATOR;
	if (result < 0)
		return (FT_ERROR);
	str = (char *)malloc(result * sizeof(char));
	if (!str)
		return (FT_ERROR);
	ft_vsnprintf(str, (size_t)result, format, ap);
	result = write(fd, str, result);
	free(str);
	return (result);
}

//dprintf()'s va_list function. takes filedescriptor.
int ft_vdnprintf(int fd, size_t size, const char *format, va_list ap)
{
	char	*str;
	size_t	actualsize;
	int		result;

	result = ft_vsnprintf(NULL, 0, format, ap) + FT_TERMINATOR;
	if (result < 0)
		return (FT_ERROR);
	actualsize = (size <= (size_t)result) * size + (size > (size_t)result) * result; 
	str = (char *)malloc(actualsize * sizeof(char));
	if (!str)
		return (FT_ERROR);
	ft_vsnprintf(str, actualsize, format, ap);
	result = write(fd, str, result);
	free(str);
	return (result);
}
