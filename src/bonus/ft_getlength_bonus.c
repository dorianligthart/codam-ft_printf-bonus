/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlength_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:14:18 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/11 20:08:03 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

// returns length of an argument.
int	ft_printf_getarglength(int conversion, void *item,
							t_conv *conv, int arglen)
{
	if (conversion == 'c' || conversion == '%')
		return (1);
	if (conversion == 's')
		return (ft_strlen((const char *)item));
	if (conversion == 'p')
		return (ft_longlen((long)item, 16));
	if (conversion == 'd' || conversion == 'i')
		return (ft_longlen((long)item, 10)
				+ (int)conv->plus + (int)conv->space);
	if (conversion == 'u')
		return (ft_longlen((long)item, 10));
	if (conversion == 'o')
		return (ft_longlen((long)item, 8) + (int)conv->hash);
	if (conversion == 'x' || conversion == 'X')
		return (ft_longlen((long)item, 16) + (int)conv->hash * 2);
	return (ERROR_FT_PRINTF);
}

//TODO: arglen if arg is integer type and has precision.
static int	get_len(bool conv_is_integer, int arglen, int fw, int pr)
{
	if (conv_is_integer)
	{
		if (arglen >= pr && arglen >= fw)
			return (arglen);
		if (pr > -1 && pr < arglen && pr > fw)
			return (ERROR_FT_PRINTF);
		return (fw);
	}
	else
	{
		if (arglen >= pr && arglen >= fw)
			return (arglen);
		if (pr > -1 && pr < arglen && pr > fw)
			return (pr);
		return (fw);
	}
}

// returns length of an argument + precision + fieldwidth.
int	ft_printf_getitemlength(int conversion, void *item,
								t_conv *conv, int arglen)
{
	if (conversion == 'c' || conversion == '%')
		return (get_len(false, 1, conv->fieldwidth, -1));
	if (conversion == 's')
		return (get_len(false, ft_strlen((const char *)item),
				conv->fieldwidth, conv->precision));
	if (conversion == 'p')
		return (get_len(true, ft_longlen((long)item, 16) + 2,
				conv->fieldwidth, conv->precision));
	if (conversion == 'd' || conversion == 'i')
		return (get_len(true, ft_longlen((long)item, 10)
				+ (int)conv->plus + (int)conv->space,
				conv->fieldwidth, conv->precision));
	if (conversion == 'u')
		return (get_len(true, ft_longlen((long)item, 10),
				conv->fieldwidth, conv->precision));
	if (conversion == 'o')
		return (get_len(true, ft_longlen((long)item, 8) + (int)conv->hash,
				conv->fieldwidth, conv->precision));
	if (conversion == 'x' || conversion == 'X')
		return (get_len(true, ft_longlen((long)item, 16)
				+ (int)conv->hash * 2,
				conv->fieldwidth, conv->precision));
	return (ERROR_FT_PRINTF);
}
