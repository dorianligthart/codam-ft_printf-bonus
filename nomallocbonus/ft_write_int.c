/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:21:15 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/10 12:02:02 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "ft_printf.h"

static int	ft_write_actual_int(int fd, int integer, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	if (integer == INT_MIN)
		return (write(fd, "-2147483648", 11));
	else if (integer < 0)
	{
		x = write(fd, "-", 1);
		integer *= -1;
	}
	else if ((*data).plus)
		x = write(fd, "+", 1);
	else if ((*data).space)
		x = write(fd, " ", 1);
	y = ft_putulong(fd, (unsigned long)integer, "0123456789", (*data).zero);
	return (-1 + (x >= 0 && y >= 0) * (x + y + 1));
}

//	flags="-+ 0", fieldwidth, precision.
int	ft_write_int(int fd, char c, va_list *list, t_data *data)
{
	int			integer;
	int			len;
	int			x;
	int			y;

	(void)c;
	x = 0;
	integer = va_arg(*list, int);
	len = ft_longlen(integer, 10);
	if ((*data).precision > len)
		(*data).zero = (*data).precision - len;
	else if ((*data).zero && (*data).width > len + (*data).space + (*data).plus)
		(*data).zero = (*data).width - (len + (*data).space + (*data).plus);
	if (!(*data).minus && (*data).width > ((*data).zero + len))
		x = ft_putchr_repeat(fd, (*data).width - ((*data).zero + len + (*data).space
					+ (*data).plus), "                                         ");
	y = ft_write_actual_int(fd, integer, data);
	if ((*data).minus && (*data).width > (*data).zero + len)
		x = ft_putchr_repeat(fd, (*data).width - ((*data).zero + len + (*data).space
					+ (*data).plus), "                                         ");
	return (-1 + (x >= 0 && y >= 0) * (x + y + 1));
}
