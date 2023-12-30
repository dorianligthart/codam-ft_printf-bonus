/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_longlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:53:23 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/03 20:01:44 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
