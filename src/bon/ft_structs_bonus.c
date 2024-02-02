/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:04:19 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/02 04:02:38 by doligtha         ###   ########.fr       */
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
	tmp->uniontype = 0;
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
	t_pfconv	*c;

	c = (t_pfconv *)malloc(sizeof(t_pfconv));
	if (!c)
		return (NULL);
	c->minus = false;
	c->zero = false;
	c->hash = false;
	c->space = false;
	c->plus = false;
	c->fw = 0;
	c->dot = false;
	c->precision = -1;
	c->lengthmod = 0;
	c->conv = '\0';
	c->arglen = 0;
	return (c);
}
