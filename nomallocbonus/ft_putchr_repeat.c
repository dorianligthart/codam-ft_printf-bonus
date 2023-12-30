/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchr_repeat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:03:41 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/20 16:13:27 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

//	prints n amount of characters taken from str.	
int	ft_putchr_repeat(int fd, int n, const char *str)
{
	int			len;
	int			x;
	int			ret;
	int			strlen;

	strlen = 0;
	while (str && str[strlen])
		strlen++;
	ret = n;
	len = n % strlen;
	while (fd >= 0 && n && str && len > 0)
	{
		x = write(fd, str, len);
		if (x < 0)
			return (x);
		n -= strlen;
		len = n % strlen;
	}
	return (ret);
}
