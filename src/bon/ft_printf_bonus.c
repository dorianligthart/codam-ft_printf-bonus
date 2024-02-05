/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:26:54 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 03:05:50 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h" //ft_atoi(), ft_strchr(), 
#include <stdarg.h>
#include <stdbool.h>

static void	set_lengthmod(const char *format, int *i, t_pfconv *conv)
{
	if (format[*i] == 'h' && ++(*i))
	{
		conv->lengthmod = 2;
		if (format[*i] == 'h' && ++(*i))
			conv->lengthmod = 1;
	}
	else if (format[*i] == 'l' && ++(*i))
	{
		conv->lengthmod += 3;
		if (format[*i] == 'l' && ++(*i))
			conv->lengthmod = 4;
	}
	else if (format[*i] == 'j' && ++(*i))
		conv->lengthmod = 5;
	else if (format[*i] == 'z' && ++(*i))
		conv->lengthmod = 6;
	else if (format[*i] == 't' && ++(*i))
		conv->lengthmod = 7;
	else if (format[*i] == 'L' && ++(*i))
		conv->lengthmod = 8;
}

static void	width_precision(const char *format, int *i,
							va_list *list, int *width_precision)
{
	va_list	tmp;
	int		atoi;
	int		va;

	va = false;
	if (format[*i] == '*' && ++(*i))
		va = true;
	atoi = 0;
	if (format[*i] >= '0' && format[*i] <= '9')
		atoi = ft_atoi(format + *i);
	while (format[*i] >= '0' && format[*i] <= '9')
		++(*i);
	if ((va && atoi && format[*i] == '$' && ++(*i)) || (va && atoi))
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

static void	parse_format(const char *format, int *i,
							va_list *list, t_pfconv *conv)
{
	while (ft_strchr("-0# +", format[*i]))
	{
		conv->minus = (bool)(conv->minus || format[*i] == '-');
		conv->zero = (bool)(conv->zero || format[*i] == '0');
		conv->hash = (bool)(conv->hash || format[*i] == '#');
		conv->space = (bool)(conv->space || format[*i] == ' ');
		conv->plus = (bool)(conv->plus || format[*i] == '+');
		(*i)++;
	}
	if ((format[*i] >= '0' && format[*i] <= '9') || format[*i] == '*')
		width_precision(format, i, list, &conv->fw);
	if (format[*i] == '.' && ++(*i))
		conv->dot = true;
	if (format[*i - 1] == '.')
		width_precision(format, i, list, &conv->precision);
	if (conv->fw < 0)
	{
		conv->fw *= -1;
		conv->minus = true;
	}
	if (format[*i] == 'h' || format[*i] == 'l' || format[*i] == 'j'
		|| format[*i] == 'z' || format[*i] == 't' || format[*i] == 'L')
		set_lengthmod(format, i, conv);
	if (ft_strchr("csdioxXufFeEaAgGnp", format[*i]))
		conv->c = format[(*i)++];
}

static bool	pfstr_pfarg(const char *format, int *i, \
							va_list *list, t_pflist *n)
{
	if (!n)
		return (false);
	if (format[*i] != '%')
	{
		n->itemlen = 0;
		while (format[*i + n->itemlen] && format[*i + n->itemlen] != '%')
			n->itemlen++;
		n->item.s = (char *)format;
		*i += n->itemlen;
	}
	else
	{
		n->conv = ft_newpfconv();
		if (!n->conv)
			return (false);
		parse_format(format, i, list, n->conv);
		if (n->conv->c == 0)
			return (false);
		if (n->conv->plus)
			n->conv->space = false;
		ft_pf_set_va_arg(&n->item, list, n->conv->lengthmod, n->conv->c);
		n->itemlen = ft_pf_itemlen(&n->item, n->conv, n->conv->c);
	}
	return (true);
}

int	ft_printf(const char *format, ...)
{
	va_list		list;
	int			i;
	t_pflist	*origin;
	int			fd;

	if (!format)
		return (ERROR_FTPRINTF);
	origin = NULL;
	va_start(list, format);
	i = 0;
	while (format[i])
		if (!pfstr_pfarg(format, &i, &list, ft_newpflist_append(&origin)))
			return (ft_pflistclear(origin), ERROR_FTPRINTF);
	va_end(list);
	fd = 1;
	return (ft_pf_printpflist(fd, origin, origin, 0));
}
