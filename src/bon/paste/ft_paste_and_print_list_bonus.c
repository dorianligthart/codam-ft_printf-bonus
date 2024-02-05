/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste_and_print_list_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 00:27:59 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 02:27:30 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

static void	pasteitem(int fd, t_pflist *node, char *dst, t_pfconv *conv)
{
	int	i;

	i = -1;
	while (conv == NULL && ++i < len)
		*(dst + i) = *(node->item.s + i);
	if (conv)
		ft_printf_printpflist(1, node, 0);
}

int	ft_printf_printpflist(int fd, t_pflist *origin, int total)
{
	t_pflist	*node;
	char		*dst;
	char		*tmp;

	node = origin;
	while (node)
	{
		if (node->itemlen == ERROR_FTPRINTF)
			return (ft_pflistclear(origin), ERROR_FTPRINTF);
		total += node->itemlen;
		node = node->next;
	}
	dst = (char *)malloc(total * sizeof(char));
	tmp = dst;
	node = origin;
	while (dst && node)
	{
		pasteitem(fd, node, tmp, node->conv);
		tmp += node->itemlen;
		node = node->next;
	}
	total = write(fd, dst, total);
	return (free(dst), ft_pflistclear(origin), total);
}
