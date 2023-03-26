/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 20:22:39 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/26 14:34:40 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	ft_isspace(char c)
{
	return (c == '\n' || c == '\f' || c == '\t'
		|| c == '\v' || c == '\r' || c == ' ');
}

/*
Description:
The atoi() function converts the initial portion of the string,
pointed to by str, to int representation. 
Taking in account leading space characters and leading 0's.

Return value:
The converted value or 0 on error.
*/
int	ft_atoi(const char *str)
{
	int	result;
	int	index;

	result = 0;
	while (ft_isspace(*str))
		str++;
	while ((char)str == '0')
		str++;
	index = 0;
	if ((str[0] == '+') || (str[0] == '-'))
		index++;
	while (str[index] >= '0' && str[index] <= '9')
		result = (result * 10) + (str[index++] - '0');
	if (str[0] == '-')
		result *= -1;
	return (result);
}
