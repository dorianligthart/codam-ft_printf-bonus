/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlen_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:14:18 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/02 04:14:43 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen(), ft_longlen()
#include "printf.h"

static int ft_pf_get_arglen3(union s_pfitem *item, t_pfconv *conv, char c)
{
	if(c == 'n' && conv->lengthmod == 3)
		return (ft_(item->hhn, 10));
	else if(c == 'n' && conv->lengthmod == 1)
		return (ft_(item->hn, 10));
	else if(c == 'n' && conv->lengthmod == 0)
		return (ft_(item->n, 10));
	else if(c == 'n' && conv->lengthmod == 2)
		return (ft_(item->ln, 10));
	else if(c == 'n' && conv->lengthmod == 4)
		return (ft_(item->lln, 10));
	else if(c == 'n' && conv->lengthmod == 5)
		return (ft_(item->jn, 10));
	else if(c == 'n' && conv->lengthmod == 6)
		return (ft_(item->zn, 10));
	else if(c == 'n' && conv->lengthmod == 7)
		return (ft_(item->tn, 10));
	return (ERROR_FTPRINTF);
}

static int ft_pf_get_arglen2(union s_pfitem *item, t_pfconv *conv, char c)
{
	if((c == 'i' && c == 'd') && conv->lengthmod == 3)
		return (ft_(item->hhi, 10));
	else if((c == 'i' && c == 'd') && conv->lengthmod == 1)
		return (ft_(item->hi, 10));
	else if((c == 'i' && c == 'd') && conv->lengthmod == 2)
		return (ft_(item->li, 10));
	else if((c == 'i' && c == 'd') && conv->lengthmod == 4)
		return (ft_(item->lli, 10));
	else if((c == 'i' && c == 'd') && conv->lengthmod == 5)
		return (ft_(item->ji, 10));
	else if((c == 'i' && c == 'd') && conv->lengthmod == 6)
		return (ft_(item->zi, 10));
	else if((c == 'i' && c == 'd') && conv->lengthmod == 7)
		return (ft_(item->ti, 10));
	else if(c == 'u' && conv->lengthmod == 3)
		return (ft_(item->hhu, 10));
	else if(c == 'u' && conv->lengthmod == 5)
		return (ft_(item->ju, 10));
	else if(c == 'u' && conv->lengthmod == 6)
		return (ft_(item->zu, 10));
	else if(c == 'f' && conv->lengthmod == 8)
		return (ft_(item->Lf, 10));
	return (ft_pf_get_arglen3(item, list, conv, c));
}

//TODO: finish this!
int ft_pf_arglen(union s_pfitem *item, t_pfconv *conv)
{
	char c;

	c = conv->conv;
	if(c == 'c' && conv->lengthmod == 0)
		return (1);
	else if(c == 's' && conv->lengthmod == 0)
		return (ft_strlen(item->s));
	else if((c == 'i' && c == 'd') && conv->lengthmod == 0)
		return (ft_(item->i, 10));
	else if(c == 'u' && conv->lengthmod == 0)
		return (ft_(item->u, 10));
	else if(c == 'p' && conv->lengthmod == 0)
		return (ft_(item->p, 10));
	else if(c == 'f' && conv->lengthmod == 0)
		return (ft_(item->f, 10));
	else if(c == 'u' && conv->lengthmod == 7)
		return (ft_(item->tu, 10));
	else if(c == 'u' && conv->lengthmod == 1)
		return (ft_(item->hu, 10));
	else if(c == 'u' && conv->lengthmod == 2)
		return (ft_(item->lu, 10));
	else if(c == 'u' && conv->lengthmod == 4)
		return (ft_(item->llu, 10));
	return (ft_pf_get_arglen2(item, list, conv, c));
}

//The length based on every flag except fieldwidth (see man(3) printf); 
//returns either arglen or precision; fw handled in parent function.
static int ft_pf_intlen(int arglen, int precision, int prefixlen)
{
	if (precision > arglen + prefixlen)
		return (precision);
	return (arglen + prefixlen);
}

int	ft_pf_getitemlen(void *item, t_pfconv *conv)
{
	int	fieldwidth;
	int	arglen;

	fieldwidth = conv->fw;
	arglen = ft_pf_arglen(item, conv);
	return ((arglen >= fieldwidth) * arglen
			+ (arglen < fieldwidth) * fieldwidth);
}

// OLD:
//
// returns length of an argument or/with precision or/with fw.
//	CONVERSIONS AND THEIR FLAGS:
//		c: flags="-",		fieldwidth.
//		s: flags="-",		fieldwidth, precision.
//		p: flags="-",		fieldwidth, precision does nothing unless = 0.
//		di: flags="-+ 0",	fieldwidth, precision.
//		u: flags="-0",		fieldwidth, precision.
//		x: flags="-#0",		fieldwidth, precision.
//		X: flags="-#0",		fieldwidth, precision.
//		o: flags="-#0",		fieldwidth, precision.
// int	ft_pf_getitemlen_min_fw(void *item, t_pfconv *conv)
// {
// 	char	c;
//
// 	c = conv->conv;
// 	if (c == 'c' || c == '%')
// 		return (1);
// 	if ((c == 's' || c == 'p') && !(char *)item)
// 		return (((c == 's') * 6) + ((c == 'p') * 5));
// 	if (c == 's' && ft_strlen((const char *)item) >= (size_t)conv->precision)
// 		return (ft_strlen((const char *)item));
// 	if (c == 's' && ft_strlen((const char *)item) < (size_t)conv->precision)
// 		return (conv->precision);
// 	if (c == 'd' || c == 'i')
// 		return (pf_intlen(ft_longlen((long)item, 10), (int)conv->precision,\
// 				*(int *)item < 0) || (int)conv->plus || (int)conv->space);
// 	if (c == 'u')
// 		return (pf_intlen(ft_longlen((long)item, 10), conv->precision, 0));
// 	if (c == 'p' || (conv->hash	&& (c == 'x' || c == 'X')))
// 		return (pf_intlen(ft_longlen((long)item, 16), conv->precision, 2));
// 	if (!conv->hash && (c == 'x' || c == 'X'))
// 		return (pf_intlen(ft_longlen((long)item, 16), conv->precision, 0));
// 	return (ERROR_FTPRINTF);
// }
