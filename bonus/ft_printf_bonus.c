/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:26:54 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/08 03:18:18 by doligtha         ###   ########.fr       */
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
}

//	parses the format string flags into 'origin->data.*'.
static int	parse(const char *format, va_list *list,
					t_comp *arg, t_data *d)
{
	char	*data[127];
	int		i;

	ft_arg_to_array(data, "-0# +.cwp", &d->minus, &d->zero, &d->hash, &d->space,
				&d->plus, &d->width, &d->dot, &d->precision, &d->conversion);
	i = 0;
	while (ft_strchr("-0# +", format[i]))
		*(*data + format[i++]) = true;
	if (format[i] >= '0' && format[i] <= '9')
		ft_printf_width_precision(*data['w'], format, i, list);
	if (format[i] == '.' && ++i)
	*data['.'] = true;
	if (format[i] >= '0' && format[i] <= '9')
		ft_printf_width_precision(*data['p'], format, i, list);
	if (*data['w']) < 0
	{
		*data['w'] *= -1;
	*data['-'] = true;
	}
if (*data['+'])
	*data[' '] = false;
	if (ft_strchr("cspdiuxX%o", format[i++]))
		*data['c'] = format[i - 1];
	arg->len = ft_printf_get_arg_len(arg, d, 1);
	return (i);
}

//	appends a new t_comp node.
//	saves:		pointer to format_string(begin or after arguments) or argument.
//	calculates:	string length (until '%' or '\0') or argument length.
//	sets next to NULL.
static int	ft_str_arg(const char *format, int *i,
						va_list *list, t_comp **object)
{
	t_data *data;

	*object = ft_newcomp_append(object);
	if (!*object)
		return (ERROR_FT_PRINTF_BONUS);
	if (format[*i] == '%')
	{
		data = ft_newdata();
		if (!data)
			return (ERROR_FT_PRINTF_BONUS);
		(*object)->item = va_arg(*list, void *);
		i += parse(format + i, list, object, data);
	}
	else
	{
		(*object)->len = 0;
		while (format[*i + (*object)->len] && format[*i + (*object)->len] != '%')
			(*object)->len++;
		(*object)->item = (char *)(format + *i);
	}
	if (!(*object)->data.conversion)
	return (1);
}

//	ft_printf() uses:	(argc * 20 + (argc - 1) * 15) bytes of stack memory.
//		- except ft_printf(NULL) which uses 0.
//	Systemcalls:		1 malloc() call, 1 write() call.
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
	return (ft_print_comp(fd, origin));
}
