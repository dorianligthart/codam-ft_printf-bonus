/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:26:54 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/02 03:57:27 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h" //ft_atoi(), ft_strchr(), 
#include <stdarg.h>
#include <stdbool.h>

static void set_lengthmod(const char *format, int *i, t_pfconv *c)
{
	if (format[*i] == 'h' && ++(*i))
	{
		c->lengthmod += 1;
		if (format[*i] == 'h' && ++(*i))
			c->lengthmod += 1;
	}
	else if (format[*i] == 'l' && ++(*i))
	{
		c->lengthmod += 2;
		if (format[*i] == 'l' && ++(*i))
			c->lengthmod += 2;
	}
	else if (format[*i] == 'j' && ++(*i))
		c->lengthmod = 5;
	else if (format[*i] == 'z' && ++(*i))
		c->lengthmod = 6;
	else if (format[*i] == 't' && ++(*i))
		c->lengthmod = 7;
	else if (format[*i] == 'L' && ++(*i))
		c->lengthmod = 8;
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
							va_list *list, t_pfconv *c)
{
	while (ft_strchr("-0# +", format[*i]))
	{
		c->minus = (bool)(c->minus || format[*i] == '-');
		c->zero = (bool)(c->zero || format[*i] == '0');
		c->hash = (bool)(c->hash || format[*i] == '#');
		c->space = (bool)(c->space || format[*i] == ' ');
		c->plus = (bool)(c->plus || format[*i] == '+');
		(*i)++;
	}
	if ((format[*i] >= '0' && format[*i] <= '9') || format[*i] == '*')
		width_precision(format, i, list, &c->fw);
	if (format[*i] == '.' && ++(*i))
		c->dot = true;
	if (format[*i - 1] == '.')
		width_precision(format, i, list, &c->precision);
	if (c->fw < 0)
	{
		c->fw *= -1;
		c->minus = true;
	}
	if (   format[*i] == 'h' || format[*i] == 'l' || format[*i] == 'j'
		|| format[*i] == 'z' || format[*i] == 't' || format[*i] == 'L')
		set_lengthmod(format, i, c);
	if (ft_strchr("csdioxXufFeEaAgGnp", format[*i]))
		c->conv = format[(*i)++];
}

static bool	pfstr_pfarg(const char *format, int *i,\
							va_list *list, t_pflist *node)
{
	if (!node)
		return (false);
	if (format[*i] != '%')
	{
		node->itemlen = 0;
		while (format[*i + node->itemlen] && format[*i + node->itemlen] != '%')
			node->itemlen++;
		node->item.s = (char *)format;
		*i += node->itemlen;
	}
	else
	{
		node->conv = ft_newpfconv();
		if (!node->conv)
			return (false);
		parse_format(format, i, list, node->conv);
		if (node->conv->conv == 0)
			return (false);
		if (node->conv->plus)
			node->conv->space = false;
		ft_pf_union(&node->item, node->conv, list);
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
	return (ft_printf_printpflist(fd, origin, 0));
}

// /**
//  * @brief prototype dit in header en maak een tester folder met de files van slack
//  * int	fft_printf(const char *format, va_list tmp);
// */
// int	fft_printf(const char *format, va_list tmp)
// {
// 	va_list		list;
// 	int			i;
// 	t_pflist	*origin;
// 	int			fd;

// 	if (!format)
// 		return (ERROR_FTPRINTF);
// 	origin = (void *)0;
// 	va_copy(list, tmp);
// 	i = 0;
// 	while (format[i])
// 		if (!str_or_arg(format, &i, &list, &origin))
// 			return (ft_pflistclear(origin), ERROR_FTPRINTF);
// 	va_end(list);
// 	fd = 1;
// 	return (ft_printf_printpflist(fd, origin));
// }


// OLD ARGLEN GETTER: called like:
//		set_arglen(&node->item, list, node->conv, node->conv->conv);
//
// static void set_arglen(union s_pfitem *item, va_list *list,
// 						t_pfconv *conv, char c)
// {
// 	if (c == 'c')
// 	{
// 		item->c = (char)va_arg(*list, int);
// 		conv->arglen = sizeof(char);
// 	}
// 	if (c == 's')
// 	{
// 		item->s = va_arg(*list, char *);
// 		conv->arglen = ft_strlen(item->s);
// 	}
// 	if (c == 'p')
// 	{
// 		item->p = va_arg(*list, void *);
// 		conv->arglen = ft_longlen((long)item->p, 16);
// 	}
// 	if (c == 'd' || c == 'i')
// 	{
// 		item->i = va_arg(*list, int);
// 		conv->arglen = ft_longlen(item->i, 10);
// 	}
// 	if (c == 'u' || c == 'x' || c == 'X')
// 	{
// 		item->u = va_arg(*list, unsigned int);
// 		conv->arglen = ft_longlen(item->u, (c == 'u' * 10) + (c != 'u' * 16));
// 	}
// }
