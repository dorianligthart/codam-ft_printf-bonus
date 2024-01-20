/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:04:19 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/20 21:41:30 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

void	ft_compclear(t_comp *comp)
{
	t_comp	*temporary;

	while (comp)
	{
		temporary = comp->next;
		if (comp->conv)
			free(comp->conv);
		free(comp);
		comp = temporary;
	}
}

//	mallocs a new t_comp node; appends a new node to the last *comp node.
//	returns: new node.
t_comp	*ft_newcomp_append(t_comp **comp)
{
	t_comp	*tmp;

	tmp = (t_comp *)malloc(sizeof(t_comp));
	if (tmp)
		return (NULL);
	tmp->itemlen = 0;
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
	t_conv	*conv;

	conv = (t_conv *)malloc(sizeof(t_conv));
	if (!conv)
		return (NULL);
	conv->conv = '\0';
	conv->minus = false;
	conv->zero = false;
	conv->hash = false;
	conv->space = false;
	conv->plus = false;
	conv->fw = 0;
	conv->dot = false;
	conv->precision = -1;
	conv->len = 0;
	return (conv);
}
