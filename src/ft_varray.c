/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:08:07 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/23 14:20:17 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h> //size_t, NULL
#include <stdarg.h> //va_list, va_arg(), va_start(), va_end()
#include <limits.h>

void	ft_varray(char **array, const char *format, ...)
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
