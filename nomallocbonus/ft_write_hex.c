/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:50:35 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/29 19:01:25 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int	ft_write_actual_hex(int fd, unsigned long hex, char c, t_data *data)
{
	int	x;

	x = 0;
	if (c == 'x')
	{
		if ((*data).zero)
			x = ft_putulong(fd, hex, "0123456789abcdef", (*data).zero);
		else
			x = ft_putulong(fd, hex, "0123456789abcdef", 0);
	}
	else if (c == 'X')
	{
		if ((*data).zero)
			x = ft_putulong(fd, hex, "0123456789ABCDEF", (*data).zero);
		else
			x = ft_putulong(fd, hex, "0123456789ABCDEF", 0);
	}
	return (-1 + (x >= 0) * (x + 1));
}

//	flags="-#0", fieldwidth, precision.
int	ft_write_hex(int fd, char c, va_list *list, t_data *data)
{
	unsigned int	hex;
	int				len;
	int				x;
	int				y;
	int				z;

	x = 0;
	y = 0;
	hex = va_arg(*list, unsigned int);
	len = ft_longlen(hex, 16);
	if ((*data).precision > len)
		(*data).zero = (*data).precision - len;
	else if ((*data).zero && (*data).width > len + (*data).hash)
		(*data).zero = (*data).width - (len + (*data).hash);
	if (!(*data).minus && (*data).width > len)
		x = ft_putchr_repeat(fd, (*data).width - len, "                         ");
	if ((*data).hash && c == 'x')
		y = write(1, "0x", 2);
	if ((*data).hash && c == 'X')
		y = write(1, "0X", 2);
	z = ft_write_actual_hex(fd, (unsigned long)hex, c, data);
	if (!(*data).minus && (*data).width > len)
		x = ft_putchr_repeat(fd, (*data).width - len, "                         ");
	return (-1 + (x >= 0 && y >= 0 && z >= 0) * (x + y + z + 1));
}
