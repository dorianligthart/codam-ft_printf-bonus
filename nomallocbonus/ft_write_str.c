/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:03 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/15 17:16:08 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

//	flags="-", fieldwidth, precision.
int	ft_write_str(int fd, char c, va_list *list, t_data *data)
{
	char	*str;
	int		len;
	int		x;
	int		y;

	(void)c;
	x = 0;
	str = va_arg(*list, char *);
	if ((*data).dot)
		len = (*data).precision;
	else
		len = ft_strlen(str);
	if (!(*data).minus && (*data).width > len)
		x = ft_putchr_repeat(fd, (*data).width - len,
				"                                                           ");
	if (!str)
		y = write(fd, "(null)", 6);
	else
		y = write(fd, str, len);
	if ((*data).minus && (*data).width > len)
		x = ft_putchr_repeat(fd, (*data).width - len,
				"                                                           ");
	return (-1 + (x >= 0 && y >= 0) * (x + y + 1));
}
