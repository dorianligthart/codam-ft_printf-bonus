/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:44:30 by dligthar          #+#    #+#             */
/*   Updated: 2024/02/05 01:35:30 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h> //va_list, va_start(), va_arg(), va_end()
#include <unistd.h> //write()

static char	*pf_strchr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)(str + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(str + i));
	return (NULL);
}

static int	pf_putint(int fd, unsigned long nbr, char *basestr)
{
	unsigned long	divider;
	int				base;
	int				i;
	char			put[31];

	base = 0;
	while (basestr && basestr[base])
		base++;
	if (base < 2)
		return (-1);
	divider = 1;
	while (divider <= nbr / base)
		divider = divider * base;
	i = 0;
	while (divider)
	{
		put[i++] = basestr[nbr / divider];
		nbr = nbr % divider;
		divider = divider / base;
	}
	return (write(fd, put, i));
}

static int	pf_newformat2(int fd, const char **format, va_list *list, int tmp)
{
	int	nbr;

	if (*(*format - 1) == 'p')
	{
		nbr = va_arg(*list, unsigned long);
		if (!nbr)
			return (write(fd, "(nil)", 5));
		tmp = write(fd, "0x", 2);
		nbr = pf_putint(fd, nbr, "0123456789abcdef");
		return (-1 + (tmp >= 0 && nbr >= 0) * (tmp + nbr + 1));
	}
	else if ((*(*format - 1) == 'd' || *(*format - 1) == 'i'))
	{
		nbr = va_arg(*list, int);
		if (nbr == -2147483648)
			return (write(fd, "-2147483648", 11));
		if (nbr < 0)
		{
			tmp = write(fd, "-", 1);
			nbr *= -1;
		}
		nbr = pf_putint(fd, nbr, "0123456789");
		return (-1 + (tmp >= 0 && nbr >= 0) * (tmp + nbr + 1));
	}
	return (pf_putint(fd, va_arg(*list, unsigned int), "0123456789"));
}

static int	pf_newformat(int fd, const char **format, va_list *list, int tmp)
{
	char	*s;

	if (!pf_strchr("cspdiuxX%", **format))
		return (0);
	if (*(++*format) == '%')
		return (write(fd, "%", 1));
	else if (*(*format - 1) == 'c')
	{
		tmp = va_arg(*list, int);
		return (write(fd, &tmp, 1));
	}
	else if (*(*format - 1) == 's')
	{
		s = va_arg(*list, char *);
		if (!s)
			return (write(fd, "(null)", 6));
		while (s[tmp])
			tmp++;
		return (write(fd, s, tmp));
	}
	else if (*(*format - 1) == 'x')
		return (pf_putint(fd, va_arg(*list, unsigned int), "0123456789abcdef"));
	else if (*(*format - 1) == 'X')
		return (pf_putint(fd, va_arg(*list, unsigned int), "0123456789ABCDEF"));
	return (pf_newformat2(fd, format, list, 0));
}

int	ft_printf(const char *format, ...)
{
	va_list		list;
	int			printed;
	int			x;
	int			y;
	const char	*tmp;

	if (!format)
		return (NULL);
	va_start(list, format);
	printed = 0;
	while (*format)
	{
		tmp = format;
		while (*format && *format != '%')
			format++;
		x = write(1, tmp, format - tmp);
		y = 0;
		if (*format == '%' && format++)
			y = pf_newformat(1, &format, &list, 0);
		if (x < 0 || y < 0)
			return (NULL);
		printed = printed + x + y;
	}
	va_end(list);
	return (printed);
}
