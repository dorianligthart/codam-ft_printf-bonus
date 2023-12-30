/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:46:37 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/15 16:36:41 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include <stdio.h>

//	flags="-", fieldwidth.
int	ft_write_chr(int fd, char c, va_list *list, t_data *data)
{
	char	chr;
	int		x;
	int		y;
	int		len;

	x = 0;
	if (c != '%')
		chr = va_arg(*list, int);
	else
		chr = '%';
	len = 1;
	if (!data->minus && data->width > len)
		x = ft_putchr_repeat(fd, data->width - len,
				"                                                            ");
	y = write(fd, &chr, len);
	if (data->minus && data->width > len)
		x = ft_putchr_repeat(fd, data->width - len,
				"                                                            ");
	return (-1 + (x >= 0 && y >= 0) * (x + y + 1));
}
