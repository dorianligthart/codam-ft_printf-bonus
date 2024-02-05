/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_structs_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:04:19 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 03:07:02 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h> // 'bool' variable type, true, false
#include <stdlib.h>	 // malloc(), free()
#include "printf.h"

void	ft_pflistclear(t_pflist *pflist)
{
	t_pflist	*tmp;

	while (pflist)
	{
		tmp = pflist->next;
		if (pflist->conv)
			free(pflist->conv);
		free(pflist);
		pflist = tmp;
	}
}

//	mallocs a new t_pflist node; appends a new node to the last *pflist node.
//	returns: new node.
t_pflist	*ft_newpflist_append(t_pflist **pflist)
{
	t_pflist	*ptr;
	t_pflist	*tmp;

	tmp = (t_pflist *)malloc(sizeof(t_pflist));
	if (!tmp)
		return (NULL);
	tmp->item = (union s_pfitem){0};
	tmp->conv = NULL;
	tmp->itemlen = 0;
	tmp->next = NULL;
	if (!*pflist)
		*pflist = tmp;
	else
	{
		ptr = *pflist;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = tmp;
	}
	return (tmp);
}

t_pfconv	*ft_newpfconv(void)
{
	t_pfconv	*conv;

	conv = (t_pfconv *)malloc(sizeof(t_pfconv));
	if (!conv)
		return (NULL);
	conv->minus = false;
	conv->zero = false;
	conv->hash = false;
	conv->space = false;
	conv->plus = false;
	conv->fw = 0;
	conv->dot = false;
	conv->precision = 1;
	conv->lengthmod = 0;
	conv->c = '\0';
	conv->arglen = 0;
	return (conv);
}
