/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:26:54 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/09 01:09:03 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

//	helper function for origin->data.width and origin->data.precision.
//		 - uses width_precision integer pointer for either.
static void	ft_printf_width_precision(const char *format, int *i,
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
	if (!va)
		*width_precision = atoi;
	else if ((va && atoi && format[*i] == '$' && *i++) || (va && atoi))
	{
		va_copy(tmp, *list);
		while (va && atoi && atoi--)
			*width_precision = va_arg(tmp, int);
		va_end(tmp);
	}
	else if (va && !atoi)
		*width_precision = va_arg(*list, int);
	if (*(format + *i - 1) == '.' && !*width_precision)
		*width_precision = 0;
}

//	parses the format string flags into 'origin->data.*'.
static int	ft_parse_conv(const char *format, va_list *list,
							t_comp *node, t_conv *c)
{
	char	*conv[127];
	int		i;

	ft_arg_to_array(conv, "-0# +f.pc", &c->minus, &c->zero, &c->hash, &c->space,
		&c->plus, &c->fieldwidth, &c->dot, &c->precision, &c->conversion);
	i = 0;
	while (ft_strchr("-0# +", format[i]))
		*(*conv + format[i++]) = true;
	if (format[i] >= '0' && format[i] <= '9')
		ft_printf_width_precision(c->fieldwidth, format, i, list);
	if (format[i] == '.' && ++i)
		*conv['.'] = true;
	if (format[i - 1] == '.')
		ft_printf_width_precision(*conv['p'], format, i, list);
	if (c->fieldwidth < 0)
	{
		c->fieldwidth *= -1;
		*conv['-'] = true;
	}
	if (*conv['+'])
		*conv[' '] = false;
	if (ft_strchr("cspdiuxX%o", format[i++]))
		*conv['c'] = format[i - 1];
	node->len = ft_printf_getarglen(c->conversion, node, c, 1);
	return (i);
}

//	appends a new t_comp node.
//	saves:		pointer to format_string(begin or after arguments) or argument.
//	calculates:	string length (until '%' or '\0') or argument length.
//	sets next to NULL.
static int	ft_str_arg(const char *format, int *i,
						va_list *list, t_comp **node)
{
	t_conv	*conv;

	*node = ft_newcomp_append(node);
	if (!*node)
		return (ERROR_FT_PRINTF_BONUS);
	if (format[*i] == '%')
	{
		conv = ft_newconv();
		if (!conv)
			return (ERROR_FT_PRINTF_BONUS);
		**node.item = va_arg(*list, void *);
		*i += ft_parse_conv(format + i, list, node, conv);
		if (!conv->conversion)
			return (ERROR_FT_PRINTF_BONUS);
	}
	else
	{
		**node.len = 0;
		while (format[*i + **node.len] && format[*i + **node.len] != '%')
			**node.len++;
		**node.item = (char *)(format + *i);
	}
	return (1);
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
		return (ERROR_FT_PRINTF_BONUS);
	va_start(list, format);
	i = 0;
	while (format[i])
		if (!ft_str_arg(&origin, format, &i, &list))
			return (ERROR_FT_PRINTF_BONUS);
	va_end(list);
	fd = 1;
	return (ft_printcomp(fd, origin));
}
