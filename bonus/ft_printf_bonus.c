/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:26:54 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/30 01:47:40 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

// returns length of an argument.
static int	get_arg_len(char mode, void *arg, t_data *d)
{
	ERRORMSG("function not implemented yet!");
	return (FALSE);
}

// for data.width and data.precision.
static void	width_prec(int *widprec, const char *format, int *i, va_list *list)
{
	va_list	tmp;
	int		atoi;
	int		va;

	va = 0;
	if (format[*i] == '*' && ++*i)
		va = TRUE;
	atoi = 0;
	if (format[*i] >= '0' && format[*i] <= '9')
		atoi = ft_atoi(format + *i);
	while (format[*i] >= '0' && format[*i] <= '9')
		++*i;
	if (!va)
		*widprec = atoi;
	else if ((va && atoi && format[*i] == '$' && ++*i) || (va && atoi))
	{
		va_copy(tmp, *list);
		while (va && atoi && atoi--)
			*widprec = va_arg(tmp, int);
		va_end(tmp);
	}
	else if (va && !atoi)
		*widprec = va_arg(*list, int);
}

// parses the argument flags.
static int	parse(const char *format, int *i, va_list *list, t_comp *current)
{
	int		*da[128];
	t_data	*d;

	d = current->data;
	d->precision = -1;
	arg_array(da, "-0# +", &d->minus, &d->zero, &d->hash, &d->space, &d->plus);
	while (ft_strchr("-0# +", format[*i]))
		*(da[format[*i++]]) = TRUE;
	if (d->plus)
		d->space = FALSE;
	if (format[*i] >= '0' && format[*i] <= '9')
		width_prec(&d->width, format, i, list);
	if (format[*i] == '.' && *i++)
		d->dot = TRUE;
	if (format[*i] >= '0' && format[*i] <= '9')
		width_prec(&d->precision, format, i, list);
	if (d->width < 0)
	{
		d->width *= -1;
		d->minus = TRUE;
	}
	if (!ft_strchr("cspdiuxX%o", format[*i]))
		return (-1);
	return (get_arg_len(format[*i], current->item, current->data));
}

//	format_str or argument.
static int	str_arg(t_comp **origin, const char *format, int *i, va_list *list)
{
	t_comp	*current;
	t_comp	*ptr;

	current = (t_comp *)malloc(sizeof(t_comp *));
	if (!current)
		return (-1);
	if (format[*i] == '%')
	{
		current->item = va_arg(*list, void *);
		current->len = parse(format, i, list, current);
	}
	else
	{
		current->len = 0;
		while (format[*i + current->len] && format[*i + current->len] != '%')
			current->len++;
		current->formatsubstr = format + *i;
	}
	if (!*origin)
		return (*origin = current, 1);
	ptr = *origin;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = current;
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int			printed;
	va_list		list;
	int			i;
	t_comp		*origin;

	if (!format)
		return (-1);
	va_start(list, format);
	printed = 0;
	i = 0;
	while (format[i])
		if (!str_arg(&origin, format, &i, &list))
			return (-1);
	va_end(list);
	return (print_comp(origin));
}
