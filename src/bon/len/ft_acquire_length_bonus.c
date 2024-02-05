/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acquire_length_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:14:18 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 03:11:43 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen(), ft_longlen()
#include "printf.h"

static int	pf_flen(union s_pfitem *item, int lengthmod, char c, t_pfconv *conv)
{
	if (lengthmod == 0)
	{
		lengthmod = ft_double_len(item->f, c, conv, conv->precision);
		if (c == 'f' || c == 'F')
			return (UNIMPLEMENTED_FTPRINTF);
		else if (c == 'e' || c == 'E')
			return (UNIMPLEMENTED_FTPRINTF);
		else if (c == 'a' || c == 'A')
			return (UNIMPLEMENTED_FTPRINTF);
		else if (c == 'g' || c == 'G')
			return (UNIMPLEMENTED_FTPRINTF);
	}
	else if (lengthmod == 8)
	{
		lengthmod = ft_longdouble_len(item->Lf, c, conv, conv->precision);
		if (c == 'f' || c == 'F')
			return (UNIMPLEMENTED_FTPRINTF);
		else if (c == 'e' || c == 'E')
			return (UNIMPLEMENTED_FTPRINTF);
		else if (c == 'a' || c == 'A')
			return (UNIMPLEMENTED_FTPRINTF);
		else if (c == 'g' || c == 'G')
			return (UNIMPLEMENTED_FTPRINTF);
	}
	return (ERROR_FTPRINTF);
}

static int	pf_ulen(union s_pfitem *item, int lengthmod, char c, t_pfconv *conv)
{
	int	base;
	int	prfx;

	base = ((c == 'u') * 10) + ((c == 'x' || c == 'X') * 16) + ((c == 'o') * 8);
	prfx = (int)conv->hash * ((c == 'x' || c == 'X') * 2) + ((c == 'o') * 1);
	if (lengthmod == 0)
		return (prfx + ft_uint_len(item->u, base));
	else if (lengthmod == 1)
		return (prfx + ft_uchar_len(item->hhu, base));
	else if (lengthmod == 2)
		return (prfx + ft_ushort_len(item->hu, base));
	else if (lengthmod == 3)
		return (prfx + ft_ulong_len(item->lu, base));
	else if (lengthmod == 4)
		return (prfx + ft_ulonglong_len(item->llu, base));
	else if (lengthmod == 5)
		return (prfx + ft_uintmax_len(item->ju, base));
	else if (lengthmod == 6)
		return (prfx + ft_size_t_len(item->zu, base));
	else if (lengthmod == 7)
		return (prfx + ft_size_t_len(item->tu, base));
	return (UNREACHABLE_FTPRINTF);
}

static int	pf_len(union s_pfitem *item, int lengthmod, char c, t_pfconv *conv)
{
	if (ft_strchr("ouxX", c))
		return (pf_ulen(item, lengthmod, c, conv));
	else if (c == 'i' || c == 'd')
	{
		if (lengthmod == 0)
			return (ft_int_len(item->i, 10));
		else if (lengthmod == 1)
			return (ft_signedchar_len(item->hhi, 10));
		else if (lengthmod == 2)
			return (ft_short_len(item->hi, 10));
		else if (lengthmod == 3)
			return (ft_long_len(item->li, 10));
		else if (lengthmod == 4)
			return (ft_longlong_len(item->lli, 10));
		else if (lengthmod == 5)
			return (ft_intmax_len(item->ji, 10));
		else if (lengthmod == 6)
			return (ft_ssize_t_len(item->zi, 10));
		else if (lengthmod == 7)
			return (ft_ptrdiff_t_len(item->ti, 10));
	}
	else if (c == 'p')
		return (ft_size_t_len((size_t)item->p, 10) + 2);
	return (pf_flen(item, lengthmod, c, conv));
}

//	sets co->arglen accordingly;
//	returns co->fw or co->arglen so it wil return itemlen;
int	ft_pf_itemlen(union s_pfitem *item, t_pfconv *co, char c)
{
	if (c == 'c')
		co->arglen = 1;
	else if (c == 's')
	{
		co->arglen = ft_strlen(item->s);
		if (co->dot && co->precision < co->arglen)
			co->arglen = co->precision;
	}
	else if (c == 'n')
		return (co->arglen = 0, 0);
	else
		co->arglen = pf_len(item, co->lengthmod, c, co);
	if (ft_strchr("dioxXup", c) && co->precision > co->arglen)
		co->arglen = co->precision;
	return (((co->fw <= co->arglen) * co->arglen)
		+ ((co->fw > co->arglen) * co->fw));
}
