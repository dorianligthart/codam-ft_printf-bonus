/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 14:39:52 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/19 14:36:13 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

#include <stddef.h>
#include <stdlib.h>

char	*ft_itoa_base(int n, char *base) // "01234567"
{
	char	*result;
	int		base_len;
	int		result_len;

	base_len = ft_strlen(base);
	result_len = ft_intlen_base(n, base_len);
	result = (char *)malloc(result_len * sizeof(char) + 1);
	if (!result)
		return (NULL);
	result[result_len--] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n = n * -1;
	}
	if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[result_len] = base[n % base_len];
		n = n / base_len;
		result_len--;
	}
	return (result);
}

// int main(int argc, char const *argv[])
// {
// 	ft_itoa_base(4000, "0123456789ABCDEF");
// 	return 0;
// }
