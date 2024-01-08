/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:14:18 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/08 02:34:19 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

static int	ft_printf_get_arg_len2(t_comp *node, t_data *data)
{
	return (0);
}

// returns length of an argument.
int	ft_printf_get_arg_len(t_comp *node, t_data *data, int len)
{
	if (data->conversion == 'c')
		return ((data->width > len) * data->width + 1);
	else if (data->conversion == 's')
	{
		len = ft_strlen(node->item);	
		return ();
	}
	else
		return (ft_printf_get_arg_len2(node, data));
}