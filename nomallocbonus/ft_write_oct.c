/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_oct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:22:48 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/10 12:01:54 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

//	flags="-#0", fieldwidth, precision.
int	ft_write_oct(int fd, char c, va_list *list, t_data *data)
{
	unsigned int	oct;
	int				len;
	int				x;
	int				y;
	int				z;

	(void)c;
	x = 0;
	y = 0;
	oct = va_arg(*list, unsigned int);
	len = ft_longlen(oct, 8);
	if ((*data).zero && (*data).precision > len + (*data).hash)
		(*data).zero = (*data).precision - ft_longlen(oct, 8);
	if (!(*data).minus && (*data).width > len + (*data).hash + (*data).zero)
		x = ft_putchr_repeat(fd, (*data).width - (len + (*data).hash + (*data).zero),
				"                                                           ");
	if ((*data).hash)
		y = write(fd, "0o", 2);
	z = ft_putulong(fd, (unsigned long)oct, "01234567", (*data).zero);
	if ((*data).minus && (*data).width > len + (*data).hash + (*data).zero)
		x = ft_putchr_repeat(fd, (*data).width - (len + (*data).zero),
				"                                                           ");
	return (-1 + (x >= 0 && y >= 0 && z >= 0) * (x + y + z + 1));
}
