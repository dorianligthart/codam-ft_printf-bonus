/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_getlen_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:14:18 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/01 01:57:56 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//The length based on every flag except fieldwidth (see man(3) printf); 
//returns either arglen or precision; fw handled in parent function.
static int printflen(int arglen, int precision, int prefixlen)
{
	return (((precision > arglen + prefixlen) * precision) +
			(precision <= arglen + prefixlen) * (arglen + prefixlen));
}	

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
int	ft_pf_getitemlen_min_fw(void *item, t_conv *conv)
{
	char	c;

	c = conv->conv;
	if (c == 'c' || c == '%')
		return (1);
	if ((c == 's' || c == 'p') && !(char *)item)
		return (((c == 's') * 6) + ((c == 'p') * 5));
	if (c == 's' && ft_strlen((const char *)item) >= (size_t)conv->precision)
		return (ft_strlen((const char *)item));
	if (c == 's' && ft_strlen((const char *)item) < (size_t)conv->precision)
		return (conv->precision);
	if (c == 'd' || c == 'i')
		return (printflen(ft_longlen((long)item, 10), (int)conv->precision,\
				*(int *)item < 0) || (int)conv->plus || (int)conv->space);
	if (c == 'u')
		return (printflen(ft_longlen((long)item, 10), conv->precision, 0));
	if (c == 'p' || (conv->hash	&& (c == 'x' || c == 'X')))
		return (printflen(ft_longlen((long)item, 16), conv->precision, 2));
	if (!conv->hash && (c == 'x' || c == 'X'))
		return (printflen(ft_longlen((long)item, 16), conv->precision, 0));
	return (ERROR_LIBFT);
}

int	ft_pf_getitemlen(void *item, t_conv *conv)
{
	int	arglen;
	int	fieldwidth;

	arglen = ft_pf_getitemlen_min_fw(item, conv);
	fieldwidth = conv->fw;
	return ((arglen >= fieldwidth) * arglen
			+ (arglen < fieldwidth) * fieldwidth);
}
