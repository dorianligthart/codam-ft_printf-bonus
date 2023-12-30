/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:23:06 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/10 12:01:38 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

//	flags="-", fieldwidth, precision==0.
int	ft_write_ptr(int fd, char c, va_list *list, t_data *data)
{
	void	*ptr;
	int		len;
	int		x;
	int		y;
	int		z;

	(void)c;
	x = 0;
	ptr = va_arg(*list, void *);
	len = ft_longlen((long)ptr, 16);
	if (!(*data).minus && (*data).width > len)
		x = ft_putchr_repeat(fd, (*data).width - len,
				"                                                           ");
	if (ptr == 0)
		return (write(fd, "(nil)", 5));
	else
	{
		y = write(1, "0x", 2);
		z = ft_putulong(fd, (unsigned long)ptr, "0123456789abcdef", (*data).zero);
	}
	if ((*data).minus && (*data).width > len)
		x = ft_putchr_repeat(fd, (*data).width - len,
				"                                                           ");
	return (-1 + (x >= 0 && y >= 0 && z >= 0) * (x + y + z + 1));
}
