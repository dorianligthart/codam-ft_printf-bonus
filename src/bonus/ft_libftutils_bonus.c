/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libftutils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:58:50 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/18 17:19:42 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h> //size_t, NULL
#include <stdarg.h> //va_list, va_arg(), va_start(), va_end()
#include <limits.h>

//returns length of integer viewed as characters.
int	ft_longlen(long n, long base)
{
	int	longlen;

	longlen = 1;
	while (n <= -base || n >= base)
	{
		n /= base;
		longlen++;
	}
	if (n < 0)
		longlen++;
	return (longlen);
}

void	ft_varray(int **array, const char *format, ...)
{
	va_list		list;
	int			i;
	char		duptable[127];

	if (!format || !*format)
		return ;
	i = -1;
	while (++i < 128)
		duptable[i] = 0;
	i = -1;
	while (format && format[++i])
	{
		if (*(duptable + format[i]))
			return ;
		*(duptable + format[i]) = '_';
	}
	va_start(list, format);
	i = -1;
	while (format[++i])
		*(array + format[i]) = (int *)va_arg(list, void *);
	va_end(list);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;

	result = 0;
	if (nptr && nptr)
	{
		while (*nptr == '\n' || *nptr == '\f' || *nptr == '\t'
			|| *nptr == '\v' || *nptr == '\r' || *nptr == ' ')
			nptr++;
		i = 0;
		if (*nptr == '-' || *nptr == '+')
			i++;
		while (nptr[i] >= '0' && nptr[i] <= '9')
			result = (result * 10) + (nptr[i++] - '0');
		if (nptr[0] == '-')
			result *= -1;	
	}
	return (result);
}
