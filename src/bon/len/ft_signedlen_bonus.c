/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signedlen_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:08:39 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 02:24:42 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//returns length of integer viewed as characters.
int	ft_signedchar_len(char n, char base)
{
	int	result;

	result = 1;
	while (n <= -base || n >= base)
	{
		n /= base;
		result++;
	}
	if (n < 0)
		result++;
	return (result);
}

//returns length of integer viewed as characters.
int	ft_short_len(short n, short base)
{
	int	result;

	result = 1;
	while (n <= -base || n >= base)
	{
		n /= base;
		result++;
	}
	if (n < 0)
		result++;
	return (result);
}

//returns length of integer viewed as characters.
int	ft_int_len(int n, int base)
{
	int	result;

	result = 1;
	while (n <= -base || n >= base)
	{
		n /= base;
		result++;
	}
	if (n < 0)
		result++;
	return (result);
}

//returns length of integer viewed as characters.
int	ft_long_len(long n, long base)
{
	int	result;

	result = 1;
	while (n <= -base || n >= base)
	{
		n /= base;
		result++;
	}
	if (n < 0)
		result++;
	return (result);
}

//returns length of integer viewed as characters.
int	ft_longlong_len(long long n, long long base)
{
	int	result;

	result = 1;
	while (n <= -base || n >= base)
	{
		n /= base;
		result++;
	}
	if (n < 0)
		result++;
	return (result);
}
