
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isxdigit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 15:47:32 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/16 15:54:17 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isxdigit(int arg)
{
	if ((arg >= '0' && arg <= '9' ) ||
		(arg >= 'A' && arg <= 'F' ) ||
		(arg >= 'a' && arg <= 'f' ))
		return (1);
	return (0);
}