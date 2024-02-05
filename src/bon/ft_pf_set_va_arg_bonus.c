/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_set_va_arg_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:47:48 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 03:08:38 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include <stdarg.h>

static void	set_union3(union s_pfitem *item, va_list *list, int lm, char c)
{
	if (c == 'n')
	{
		if (lm == 0)
			item->n = va_arg(*list, int *);
		else if (lm == 1)
			item->hhn = va_arg(*list, signed char *);
		else if (lm == 2)
			item->hn = va_arg(*list, short *);
		else if (lm == 3)
			item->ln = va_arg(*list, long *);
		else if (lm == 4)
			item->lln = va_arg(*list, long long *);
		else if (lm == 5)
			item->jn = va_arg(*list, intmax_t *);
		else if (lm == 6)
			item->zn = va_arg(*list, size_t *);
		else if (lm == 7)
			item->tn = va_arg(*list, ptrdiff_t *);
	}
	else if (ft_strchr("fFeEaAgG", c) && lm == 0)
		item->f = va_arg(*list, double);
	else if (ft_strchr("fFeEaAgG", c) && lm == 8)
		item->Lf = va_arg(*list, long double);
}

static void	set_union2(union s_pfitem *item, va_list *list, int lm, char c)
{
	if (c == 'p')
		item->p = va_arg(*list, void *);
	else if (c == 'u' || c == 'x' || c == 'X' || c == 'o')
	{
		if (lm == 0)
			item->u = va_arg(*list, unsigned int);
		else if (lm == 1)
			item->hhu = (unsigned char)va_arg(*list, unsigned int);
		else if (lm == 2)
			item->hu = (unsigned short)va_arg(*list, unsigned int);
		else if (lm == 3)
			item->lu = va_arg(*list, unsigned long);
		else if (lm == 4)
			item->llu = va_arg(*list, unsigned long long);
		else if (lm == 5)
			item->ju = va_arg(*list, uintmax_t);
		else if (lm == 6)
			item->zu = va_arg(*list, size_t);
		else if (lm == 7)
			item->tu = va_arg(*list, ptrdiff_t);
	}
	else
		set_union3(item, list, lm, c);
}

void	ft_pf_set_va_arg(union s_pfitem *item, va_list *list,
								int lm, char c)
{
	if (c == 'c')
		item->c = (char)va_arg(*list, int);
	else if (c == 's')
		item->s = va_arg(*list, char *);
	else if (c == 'i' || c == 'd')
	{
		if (lm == 0)
			item->i = va_arg(*list, int);
		else if (lm == 1)
			item->hhi = (signed char)va_arg(*list, int);
		else if (lm == 2)
			item->hi = (short)va_arg(*list, int);
		else if (lm == 3)
			item->li = va_arg(*list, long);
		else if (lm == 4)
			item->lli = va_arg(*list, long long);
		else if (lm == 5)
			item->ji = va_arg(*list, intmax_t);
		else if (lm == 6)
			item->zi = va_arg(*list, size_t);
		else if (lm == 7)
			item->ti = va_arg(*list, ptrdiff_t);
	}
	else
		set_union2(item, list, lm, c);
}
