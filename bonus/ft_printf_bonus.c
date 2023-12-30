/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:26:54 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/30 17:46:31 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

//	for origin->data.width and origin->data.precision.
static void	width_prec(int *widprec, const char *format, int *i, va_list *list)
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
		*widprec = atoi;
	else if ((va && atoi && format[*i] == '$' && *i++) || (va && atoi))
	{
		va_copy(tmp, *list);
		while (va && atoi && atoi--)
			*widprec = va_arg(tmp, int);
		va_end(tmp);
	}
	else if (va && !atoi)
		*widprec = va_arg(*list, int);
}

//	parses the format string into 'origin->data.*'.
static void	parse(t_comp **arg, const char *format, int *i, va_list *list)
{
	int		*da[128];
	t_data	*d;

	d = &(*arg)->data;
	d->precision = -1;
	arg_array(da, "-0# +", &d->minus, &d->zero,\
			&d->hash, &d->space, &d->plus);
	while (ft_strchr("-0# +", format[*i]))
		*(da[format[*i++]]) = true;
	if (d->plus)
		d->space = false;
	if (format[*i] >= '0' && format[*i] <= '9')
		width_prec(&d->width, format, i, list);
	if (format[*i] == '.' && *i++)
		d->dot = true;
	if (format[*i] >= '0' && format[*i] <= '9')
		width_prec(&d->precision, format, i, list);
	if (d->width < 0)
	{
		d->width *= -1;
		d->minus = true;
	}
	if (*(format + *i))
		d->conversion = *(format + *i++);
	(*arg)->len = ft_get_arg_len(*arg);
}

//	mallocs a new t_comp node; appends new node to comp.
//	returns: new node.
t_comp	*t_comp_append(t_comp **comp)
{
	t_comp	*tmp;

	tmp = (t_comp *)malloc(sizeof(t_comp *));
	if (!tmp)
		return (NULL);
	tmp->len = 0;
	tmp->item = NULL;
	tmp->data.conversion = '\0';
	tmp->data.minus = false;
	tmp->data.zero = false;
	tmp->data.hash = false;
	tmp->data.space = false;
	tmp->data.plus = false;
	tmp->data.dot = false;
	tmp->data.width = 0;
	tmp->data.precision = 0;
	tmp->next = NULL;
	while ((*comp)->next)
		(*comp) = (*comp)->next;
	if (!(*comp))
		(*comp) = tmp;
	else
		(*comp)->next = tmp;
	return (tmp);
}

//	saves 'a part of format string' or 'an argument' in a new t_comp node.
static int	str_arg(t_comp **object, const char *format, int *i, va_list *list)
{
	*object = t_comp_append(object);
	if (!*object)
		return (ERROR_FT_PRINTF);
	if (format[*i] == '%')
	{
		(*object)->item = va_arg(*list, void *);
		parse(object, format, i, list);
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

int	ft_printf(const char *format, ...)
{
	va_list		list;
	int			i;
	t_comp		*origin;
	int			fd;

	if (!format)
		return (ERROR_FT_PRINTF);
	va_start(list, format);
	fd = 1;
	i = 0;
	while (format[i])
		if (!str_arg(&origin, format, &i, &list))
			return (ERROR_FT_PRINTF);
	va_end(list);
	return (ft_print_comp(origin));
}
