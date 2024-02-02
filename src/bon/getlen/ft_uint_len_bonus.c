/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:08:39 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/02 03:43:08 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//returns length ochareger viewed as characters.
int	ft_ulonglen(unsigned long n, unsigned long base)
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
