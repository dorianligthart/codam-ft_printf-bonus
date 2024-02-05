/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignedlen_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:08:39 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 00:55:18 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//returns length of integer viewed as characters.
int	ft_uchar_len(unsigned char n, unsigned char base)
{
	int	result;

	result = 1;
	while (n >= base)
	{
		n /= base;
		result++;
	}
	return (result);
}

//returns length of integer viewed as characters.
int	ft_ushort_len(unsigned short n, unsigned short base)
{
	int	result;

	result = 1;
	while (n >= base)
	{
		n /= base;
		result++;
	}
	return (result);
}

//returns length of integer viewed as characters.
int	ft_uint_len(unsigned int n, unsigned int base)
{
	int	result;

	result = 1;
	while (n >= base)
	{
		n /= base;
		result++;
	}
	return (result);
}

//returns length of integer viewed as characters.
int	ft_ulong_len(unsigned long n, unsigned long base)
{
	int	result;

	result = 1;
	while (n >= base)
	{
		n /= base;
		result++;
	}
	return (result);
}

//returns length of integer viewed as characters.
int	ft_ulonglong_len(unsigned long long n, unsigned long long base)
{
	int	result;

	result = 1;
	while (n >= base)
	{
		n /= base;
		result++;
	}
	return (result);
}
