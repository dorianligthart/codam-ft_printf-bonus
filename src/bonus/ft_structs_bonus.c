/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:04:19 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/01 02:23:51 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h> // 'bool' variable type, true, false
#include <stdlib.h>	 // malloc(), free()
#include "libft.h"
#include <stdio.h>

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
	tmp->itemlen = 0;
	tmp->item = NULL;
	tmp->conv = NULL;
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

t_conv	*ft_newconv(void)
{
	t_conv	*c;

	c = (t_conv *)malloc(sizeof(t_conv));
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
	c->conv = '\0';
	c->len = 0;
	return (c);
}
