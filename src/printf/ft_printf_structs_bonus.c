/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_structs_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:04:19 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/30 20:51:39 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h> // 'bool' variable type, true, false
#include <stdlib.h>	 // malloc(), free()
#include "libft.h"

void	ft_pflistclear(t_pflist *pflist)
{
	t_pflist	*temporary;

	while (pflist)
	{
		temporary = pflist->next;
		if (pflist->conv)
			free(pflist->conv);
		free(pflist);
		pflist = temporary;
	}
}

//	mallocs a new t_pflist node; appends a new node to the last *pflist node.
//	returns: new node.
t_pflist	*ft_newpflist_append(t_pflist **pflist)
{
	t_pflist	*tmp;
	t_pflist	*ptr;

	tmp = (t_pflist *)malloc(sizeof(t_pflist));
	if (!tmp)
		return (NULL);
	tmp->itemlen = 0;
	tmp->item = NULL;
	tmp->conv = NULL;
	tmp->next = NULL;
	if (!(*pflist))
		(*pflist) = tmp;
	else
	{
		ptr = *pflist;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = tmp;
	}
	return (tmp);
}

t_conv	*ft_newconv(void)
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
