/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:24:49 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/30 02:00:04 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
// libs:
#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

//not safe: could set ' ' or '0' to true before '+' or'.' are set.
static void	conv_flags(char **format, t_data *data)
{
	if (**format == '-')
		(*data).minus = 1;
	else if (**format == '0')
		(*data).zero = 1;
	else if (**format == '#')
		(*data).hash = 1;
	else if (**format == ' ')
		(*data).space = 1;
	else if (**format == '+')
		(*data).plus = 1;
	++*format;
}

static void	width_prec(int *widprec, const char **format, va_list *list)
{
	va_list	tmp;
	int		atoi;
	int		va;

	va = 0;
	if (*format == '*' && *format++)
		va = 1;
	atoi = 0;
	if (*format >= '0' && *format <= '9')
		atoi = ft_atoi(*format + *i);
	while (*format >= '0' && *format <= '9')
		*format++;
	if (!va)
		*widprec = atoi;
	else if ((va && atoi && *format == '$' && *format++) || (va && atoi))
	{
		va_copy(tmp, *list);
		while (va && atoi && atoi--)
			*widprec = va_arg(tmp, int);
		va_end(tmp);
	}
	else if (va && !atoi)
		*widprec = va_arg(*list, int);
}

static int	parse_flags2(int fd, char **format, va_list *list, t_data *data)
{
	static int	(*f[128])(int, char, va_list *, t_data *) = \
	{['%'] = ft_write_chr, ['c'] = ft_write_chr, ['s'] = ft_write_str, \
	['d'] = ft_write_int, ['i'] = ft_write_int, ['u'] = ft_write_uint, \
	['x'] = ft_write_hex, ['X'] = ft_write_hex, ['p'] = ft_write_ptr, \
	['o'] = ft_write_oct};

	if (((**format == 'h' || **format == 'l') && *format++)
		|| (**format == 'h' || **format == 'l' || **format == 'j'
			|| **format == 'z' || **format == 't' || **format == 'L'))
		++*format;
	if (!ft_strchr("cspdiuxX%o", **format) && *(*format++))
		return (-1);
	++*format;
	return ((*f[(int)*(*format - 1)])(fd, *(*format - 1), list, data));
}

static int	parse_flags(int fd, char **format, va_list *list)
{
	t_data		data;

	data = (t_data){0};
	data.precision = -1;
	while (ft_strchr("# +-0", **format))
		conv_flags(format, &data);
	if (data.plus)
		data.space = 0;
	if ((**format >= '1' && **format <= '9') || **format == '*')
		width_prec(&data.width, format, &data, list);
	if (**format == '.' && *format++)
		data.dot = 1;
	if ((**format >= '0' && **format <= '9') || **format == '*')
		width_prec(&data.precision, format, &data, list);
	if (data.dot)
		data.zero = 0;
	return (parse_flags2(fd, format, list, &data));
}

// original printf:
//		http://www.generic-programming.org/_dgregor/cpp/ct_performance.png
// mine:
//		way worse, but logical output.
// ft_printf uses: no malloc calls, some stack memory (for conversion "diuxXo"),
//		(1 + ('%' in format)) * write()'s, where "%%" counts as 1 write().
int	ft_printf(const char *format, ...)
{
	va_list		list;
	int			printed;
	int			x;
	int			y;
	const char	*tmp;

	if (!format)
		return (-1);
	va_start(list, format);
	printed = 0;
	while (*format)
	{
		tmp = format;
		while (*format && *format != '%')
			format++;
		x = write(1, tmp, format - tmp);
		y = 0;
		if (*format == '%' && format++)
			y = parse_flags(1, (char **)&format, &list);
		if (y < 0 || x < 0)
			return (-1);
		printed = printed + x + y;
	}
	va_end(list);
	return (printed);
}
