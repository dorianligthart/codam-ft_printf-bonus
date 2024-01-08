/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:04:19 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/08 00:58:26 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

//	mallocs a new t_comp node; appends new node to last *comp node.
//	returns: new node.
//	also copies fd from *comp to new.
t_comp	*ft_newcomp_append(t_comp **comp)
{
	t_comp *tmp;

	tmp = (t_comp *)malloc(sizeof(t_comp));
	if (tmp)
		return (NULL);
	tmp->len = 0;
	tmp->item = NULL;
	tmp->next = NULL;
	while ((*comp)->next)
		(*comp) = (*comp)->next;
	if (!(*comp))
		(*comp) = tmp;
	else
		(*comp)->next = tmp;
	return (tmp);
}
t_data	*ft_newdata(void)
{
	t_comp *data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ERROR_FT_PRINTF_BONUS);
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
