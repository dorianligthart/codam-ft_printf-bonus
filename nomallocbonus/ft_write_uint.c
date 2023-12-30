/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:19:24 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/10 12:10:47 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

//	flags="-0", fieldwidth, precision.
int	ft_write_uint(int fd, char c, va_list *list, t_data *data)
{
	unsigned int	uint;
	int				len;
	int				x;
	int				y;
	int				z;

	(void)c;
	x = 0;
	y = 0;
	uint = va_arg(*list, unsigned int);
	len = ft_longlen(uint, 10);
	if ((*data).precision > len)
		(*data).zero = (*data).precision - len;
	else if ((*data).zero && (*data).width > len)
		(*data).zero = (*data).width - len;
	if (!(*data).minus && (*data).width > len)
		x = ft_putchr_repeat(1, (*data).width - (len + (*data).zero), 0);
	z = ft_putulong(fd, (unsigned long)uint, "0123456789", (*data).zero);
	if (!(*data).minus && (*data).width > len)
		x = ft_putchr_repeat(1, (*data).width - (len + (*data).zero), 0);
	return (-1 + (x >= 0 && y >= 0 && z >= 0) * (x + y + z + 1));
}
