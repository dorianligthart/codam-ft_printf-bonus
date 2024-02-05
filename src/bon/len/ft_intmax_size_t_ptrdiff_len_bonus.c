/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intmax_size_t_ptrdiff_len_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:16:31 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 03:12:44 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ssize_t
#include <unistd.h>

//size_t
#include <stddef.h>

//intmax_t uintmax_t intptr_t
#include <stdint.h>

int	ft_intmax_len(intmax_t n, intmax_t base)
{
	int	result;

	result = 1;
	while (n >= base)
	{
		n /= base;
		result++;
	}
	if (n < 0)
		result++;
	return (result);
}

int	ft_uintmax_len(uintmax_t n, uintmax_t base)
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

int	ft_size_t_len(size_t n, size_t base)
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

int	ft_ssize_t_len(ssize_t n, ssize_t base)
{
	int	result;

	result = 1;
	while (n >= base)
	{
		n /= base;
		result++;
	}
	if (n < 0)
		result++;
	return (result);
}

int	ft_ptrdiff_t_len(ptrdiff_t n, ptrdiff_t base)
{
	int	result;

	result = 1;
	while (n >= base)
	{
		n /= base;
		result++;
	}
	if (n < 0)
		result++;
	return (result);
}
