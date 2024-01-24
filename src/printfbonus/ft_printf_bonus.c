/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:26:54 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/23 20:26:54 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

//	helper function for comp->conv->fw and comp->conv->precision.
//		- sets
//		- uses width_precision integer pointer for either.
static void	width_precision(const char *format, int *i,
							va_list *list, int *width_precision)
{
	va_list	tmp;
	int		atoi;
	int		va;

	va = false;
	if (format[*i] == '*' && *i++)
		va = true;
	atoi = 0;
	if (format[*i] >= '0' && format[*i] <= '9')
		atoi = ft_atoi(format + *i);
	while (format[*i] >= '0' && format[*i] <= '9')
		++*i;
	if ((va && atoi && format[*i] == '$' && *i++) || (va && atoi))
	{
		va_copy(tmp, *list);
		while (va && atoi && atoi--)
			*width_precision = va_arg(tmp, int);
		va_end(tmp);
	}
	if (!va)
		*width_precision = atoi;
	else if (va && !atoi)
		*width_precision = va_arg(*list, int);
	if (*(format + *i - 1) == '.' && !*width_precision)
		*width_precision = 0;
}

//	parses the format string flags into 'origin->data.*'.
static int	parse_format(const char *format, va_list *list, t_conv *c)
{
	int		i;
	char	*arr[127];

	ft_varray(arr, "-0# +", &c->minus, &c->zero, &c->hash, &c->space, &c->plus);
	i = 0;
	while (ft_strchr("-0# +", format[i]))
		*(*arr + format[i++]) = true;
	if (format[i] >= '0' && format[i] <= '9')
		width_precision(format, &i, list, &c->fw);
	if (format[i] == '.' && ++i)
		*arr['.'] = true;
	if (format[i - 1] == '.')
		width_precision(format, &i, list, &c->precision);
	if (c->fw < 0)
	{
		c->fw *= -1;
		*arr['-'] = true;
	}
	if (*arr['+'])
		*arr[' '] = false;
	if (ft_strchr("cspdiuxX%o", format[i]) && ++i)
		*arr['c'] = format[i - 1];
	return (i);
}

static void	parse_conversion(const char *format, int *i,
								va_list *list, t_comp *node)
{
	t_conv *c;

	c = node->conv;
	*i += parse_format(format + *i, list, c);
	if (c->conv && c->conv != '%')
		node->item = va_arg(*list, void *);
	if ((c->conv == 'd' || c->conv == 'i') && *(int *)node->item < 0)
	{
		c->plus = 0;
		c->space = 0;
	}
	c->len = ft_printf_getarglength(c->conv, node->item);
	node->itemlen = ft_printf_getitemlength(c->conv, node->item, c);
}

//	appends a new t_comp node.
//	saves:		a pointer to format_string(begin or after conversion(s))
//					or conversion to void *item.
//	calculates:	string length (until '%' or '\0') or argument length.
//	sets next to NULL.
//	Returns false if an error has occured otherwise true.
static bool	str_or_arg(const char *format, int *i, va_list *list, t_comp *origin)
{
	t_comp *node;

	node = ft_newcomp_append(&origin);
	if (!node)
		return (false);
	if (format[*i] == '%')
	{
		node->conv = ft_newconv();
		if (!node->conv)
			return (false);
		parse_conversion(format, i, list, node);
	}
	else
	{
		node->itemlen = 0;
		while (format[*i + node->itemlen]
			&& format[*i + node->itemlen] != '%')
			node->itemlen++;
		node->item = (char *)format;
		*i += node->itemlen;
	}
	return (true);
}

//	ft_printf() uses:	(argc * 20 + (argc - 1) * 15) bytes of heap memory.
//		- except ft_printf(NULL) which uses 0.
//	Systemcalls:		argc * 3 malloc()'s, 1 write().
//	Returns:			Integer of the printed characters(even '\0' from "%c"!).
int	ft_printf(const char *format, ...)
{
	va_list		list;
	int			i;
	t_comp		*origin;
	int			fd;

	if (!format)
		return (ERROR_LIBFT);
	origin = (void *)0;
	va_start(list, format);
	i = 0;
	while (format[i])
		if (!str_or_arg(format, &i, &list, origin))
			return (ft_compclear(origin), ERROR_LIBFT);
	va_end(list);
	fd = 1;
	return (ft_printf_printcomp(fd, origin));
}

// int main(int argc, char const *argv[])
// {
// 	ft_printf("hello world!\n");
// 	return 0;
// }
