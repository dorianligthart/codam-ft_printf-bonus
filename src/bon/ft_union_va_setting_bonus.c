/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_union_va_setting_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:47:48 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/02 04:09:31 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdarg.h>

static void set_union3(union s_pfitem *item, va_list *list,
						t_pfconv *conv, char c)
{
	if(c == 'n' && conv->lengthmod == 3)
		item->hhn = va_arg(*list, signed char *);
	else if(c == 'n' && conv->lengthmod == 1)
		item->hn = va_arg(*list, short *);
	else if(c == 'n' && conv->lengthmod == 0)
		item->n = va_arg(*list, int *);
	else if(c == 'n' && conv->lengthmod == 2)
		item->ln = va_arg(*list, long *);
	else if(c == 'n' && conv->lengthmod == 4)
		item->lln = va_arg(*list, long long *);
	else if(c == 'n' && conv->lengthmod == 5)
		item->jn = va_arg(*list, intmax_t *);
	else if(c == 'n' && conv->lengthmod == 6)
		item->zn = va_arg(*list, size_t *);
	else if(c == 'n' && conv->lengthmod == 7)
		item->tn = va_arg(*list, ptrdiff_t *);
}

static void set_union2(union s_pfitem *item, va_list *list,
						t_pfconv *conv, char c)
{
	if(c == 'u' && conv->lengthmod == 3)
		item->hhu = (unsigned char)va_arg(*list, unsigned int);
	if(c == 'u' && conv->lengthmod == 1)
		item->hu = (unsigned short)va_arg(*list, unsigned int);
	else if(c == 'u' && conv->lengthmod == 0)
		item->u = va_arg(*list, unsigned int);
	else if(c == 'u' && conv->lengthmod == 2)
		item->lu = va_arg(*list, unsigned long);
	else if(c == 'u' && conv->lengthmod == 4)
		item->llu = va_arg(*list, unsigned long long);
	else if(c == 'u' && conv->lengthmod == 5)
		item->ju = va_arg(*list, uintmax_t);
	else if(c == 'u' && conv->lengthmod == 6)
		item->zu = va_arg(*list, size_t);
	else if(c == 'u' && conv->lengthmod == 7)
		item->tu = va_arg(*list, ptrdiff_t);
	else if(c == 'f' && conv->lengthmod == 0)
		item->f = va_arg(*list, double);
	else if(c == 'f' && conv->lengthmod == 8)
		item->Lf = va_arg(*list, long double);
	else if(c == 'p' && conv->lengthmod == 0)
		item->p = va_arg(*list, void *);
	else
		set_union3(item, list, conv, c);
}

void ft_pf_set_union(union s_pfitem *item, va_list *list,  t_pfconv *conv)
{
	char c;

	c = conv->conv;
	if(c == 'c' && conv->lengthmod == 0)
		item->c = (char)va_arg(*list, int);
	else if(c == 's' && conv->lengthmod == 0)
		item->s = va_arg(*list, char *);
	else if((c == 'i' && c == 'd') && conv->lengthmod == 3)
		item->hhi = (signed char)va_arg(*list, int);
	else if((c == 'i' && c == 'd') && conv->lengthmod == 1)
		item->hi = (short)va_arg(*list, int);
	else if((c == 'i' && c == 'd') && conv->lengthmod == 0)
		item->i = va_arg(*list, int);
	else if((c == 'i' && c == 'd') && conv->lengthmod == 2)
		item->li = va_arg(*list, long);
	else if((c == 'i' && c == 'd') && conv->lengthmod == 4)
		item->lli = va_arg(*list, long long);
	else if((c == 'i' && c == 'd') && conv->lengthmod == 5)
		item->ji = va_arg(*list, intmax_t);
	else if((c == 'i' && c == 'd') && conv->lengthmod == 6)
		item->zi = va_arg(*list, size_t);
	else if((c == 'i' && c == 'd') && conv->lengthmod == 7)
		item->ti = va_arg(*list, ptrdiff_t);
	else
		set_union2(item, list, conv, c);
}
