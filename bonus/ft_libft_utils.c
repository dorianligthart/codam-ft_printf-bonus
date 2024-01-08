/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:58:50 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/08 01:01:38 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h> //size_t, NULL
#include <stdarg.h> //va_list, va_arg(), va_start(), va_end()

//sets &table[128]; index[format characters taken as integers] = va_list items.
void	ft_arg_to_array(void **table, const char *format, ...)
{
	va_list		list;
	int			i;
	char		duptable[127];

	if (!format || !*format || !*table)
		return ;
	i = -1;
	while (++i < 128)
		(*table)[i] = 0;
	i = -1;
	while (++i < 128)
		duptable[i] = 0;
	i = -1;
	while (format && format[++i])
	{
		if (duptable[format[i]])
			return ;
		duptable[format[i]] = '_';
	}
	va_start(list, format);
	i = -1;
	while (format[++i])
		table[format[i]] = va_arg(list, void *);
	va_end(list);
}

size_t	ft_strlen(const char *s)
{
	size_t	ret;

	ret = 0;
	while (s && s[ret])
		ret++;
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s && (unsigned char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

// strdigit longer than length of INT_MAX will be cut off near INT_MAX.
int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;

	result = 0;
	if (!nptr || !*nptr)
		return (0);
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
	nptr += i;
	return (result);
}
