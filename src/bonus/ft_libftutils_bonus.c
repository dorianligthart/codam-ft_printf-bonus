/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libftutils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:58:50 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/20 21:41:38 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h> //size_t, NULL
#include <stdarg.h> //va_list, va_arg(), va_start(), va_end()
#include <limits.h>

//returns length ochareger viewed as characters.
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

void	ft_varray(void **array, const char *format, ...)
{
	va_list		list;
	int			i;
	char		duptable[127];

	if (!format || !*format)
		return ;
	i = -1;
	while (++i < 127)
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
		*((char **)array + format[i]) = (char *)va_arg(list, void *);
	va_end(list);
}

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	if (dest && !src)
// 		return (dest);
// 	if (!dest || !src)
// 		return (NULL);
// 	while (n--)
// 		*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
// 	return (dest);
// }

// int	ft_atoi(const char *nptr)
// {
// 	int	result;
// 	int	i;

// 	result = 0;
// 	if (!nptr || !*nptr)
// 		return (0);
// 	while (*nptr == '\n' || *nptr == '\f' || *nptr == '\t'
// 		|| *nptr == '\v' || *nptr == '\r' || *nptr == ' ')
// 		nptr++;
// 	i = 0;
// 	if (*nptr == '-' || *nptr == '+')
// 		i++;
// 	while (result <= INT_MAX / 10 && nptr[i] >= '0' && nptr[i] <= '9')
// 		result = (result * 10) + (nptr[i++] - '0');
// 	if (nptr[0] == '-')
// 		result *= -1;
// 	return (result);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = -1;
// 	while (s && s[++i])
// 		if (s[i] == (unsigned char)c)
// 			return ((char *)(s + i));
// 	if (s && (unsigned char)c == '\0')
// 		return ((char *)(s + i));
// 	return (NULL);
// }

// size_t	ft_strlen(const char *s)
// {
// 	int	len;

// 	len = 0;
// 	while (s && s[len])
// 		len++;
// 	return (len);
// }
