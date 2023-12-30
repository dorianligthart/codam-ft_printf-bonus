/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putulong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:00:22 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/21 22:07:26 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h" //lol

#include <limits.h>
#include <stdio.h>

int	ft_putulong(int fd, unsigned long nbr, char *basestr, int zeros)
{
	unsigned long	divider;
	int				base;
	int				x;
	int				y;
	char			put[64];

	base = ft_strlen(basestr);
	if (base < 2)
		return (-1);
	x = ft_putchr_repeat(fd, zeros, "000000000000000000000000000000000000000");
	divider = 1;
	while (divider <= nbr / base)
		divider = divider * base;
	y = 0;
	while (divider)
	{
		put[y] = basestr[nbr / divider];
		nbr = nbr % divider;
		divider = divider / base;
		y++;
	}
	put[y] = '\0';
	y = write(fd, put, y);
	return (-1 + (x >= 0 && y >= 0) * (x + y + 1));
}

// int main()
// {
// 	// 4294967296
// 	printf("--> %d\n", ft_putulong(1, 0, "0123456789", 3));
// 	printf("--> %d\n", ft_putulong(1, ULONG_MAX, "0123456789", 0));
// 	printf("--> %d\n", ft_putulong(1, LONG_MAX, "0123456789", 0));
// 	
// 	printf("--> %d\n", ft_putulong(1, 0, "0123456789abcdef", 0));
// 	printf("--> %d\n", ft_putulong(1, ULONG_MAX, "0123456789abcdef", 0));
// 	printf("--> %d\n", ft_putulong(1, LONG_MAX, "0123456789abcdef", 0));
// 	
// 	printf("--> %d\n", ft_putulong(1, 0, "0123456789ABCDEF", 0));
// 	printf("--> %d\n", ft_putulong(1, ULONG_MAX, "0123456789ABCDEF", 0));
// 	printf("--> %d\n", ft_putulong(1, LONG_MAX, "0123456789ABCDEF", 0));
// 	
// 	printf("--> %d\n", ft_putulong(1, 0, "01", 0));
// 	printf("--> %d\n", ft_putulong(1, 1, "01", 0));
// 	printf("--> %d\n", ft_putulong(1, 2, "01", 0));
// 	printf("--> %d\n", ft_putulong(1, 3, "01", 0));
// 	printf("--> %d\n", ft_putulong(1, 4, "01", 0));
// 	printf("--> %d\n", ft_putulong(1, 5, "01", 0));
// 	printf("--> %d\n", ft_putulong(1, ULONG_MAX, "01", 0));
// 	printf("--> %d\n", ft_putulong(1, LONG_MAX, "01", 0));
// 	return 0;
// }
