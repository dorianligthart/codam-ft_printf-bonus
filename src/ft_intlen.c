/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 20:07:06 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/17 20:07:13 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_intlen(int n, int base)
{
	int	intlen;

	intlen = 1;
	while (n <= -base || n >= base)
	{
		n /= base;
		intlen++;
	}
	if (n < 0)
		intlen++;
	return (intlen);
}
