/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initstructs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:04:19 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/09 01:55:18 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

//	mallocs a new t_comp node; appends new node to last *comp node.
//	returns: new node.
//	also copies fd from *comp to new.
t_comp	*ft_newcomp_append(t_comp **comp)
{
	t_comp	*tmp;

	tmp = (t_comp *)malloc(sizeof(t_comp));
	if (tmp)
		return (NULL);
	tmp->len = 0;
	tmp->item = NULL;
	tmp->conv = NULL;
	tmp->next = NULL;
	while ((*comp)->next)
		(*comp) = (*comp)->next;
	if (!(*comp))
		(*comp) = tmp;
	else
		(*comp)->next = tmp;
	return (tmp);
}

t_conv	*ft_newdata(void)
{
	t_conv	*data;

	data = (t_conv *)malloc(sizeof(t_conv));
	if (!data)
		return (NULL);
	data->conversion = '\0';
	data->minus = false;
	data->zero = false;
	data->hash = false;
	data->space = false;
	data->plus = false;
	data->width = 0;
	data->dot = false;
	data->precision = -1;
	return (data);
}
