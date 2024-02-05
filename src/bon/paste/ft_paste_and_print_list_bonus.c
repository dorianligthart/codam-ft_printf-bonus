/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste_and_print_list_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 00:27:59 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 03:19:25 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdlib.h>

static void	pasteitem(t_pflist *node, char *dst, int len, t_pfconv *conv)
{
	int	i;

	if (conv == NULL)
	{
		i = -1;
		while (++i < len)
			*(dst + i) = *(node->item.s + i);
	}
}

static void	pf_set_n_arg(union s_pfitem *item, ptrdiff_t printed, int lm)
{
	if (lm == 0)
		*item->n = (int)printed;
	else if (lm == 1)
		*item->hhn = (signed char)printed;
	else if (lm == 2)
		*item->hn = (short)printed;
	else if (lm == 3)
		*item->ln = (long)printed;
	else if (lm == 4)
		*item->lln = (long long)printed;
	else if (lm == 5)
		*item->jn = (intmax_t)printed;
	else if (lm == 6)
		*item->zn = (size_t)printed;
	else if (lm == 7)
		*item->tn = printed;
}

int	ft_pf_printpflist(int fd, t_pflist *origin, t_pflist *node, int total)
{
	char		*dst;
	char		*tmp;

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
		if (node->conv->c == 'n')
			pf_set_n_arg(&node->item, tmp - dst, node->conv->lengthmod);
		pasteitem(node, tmp, node->itemlen, node->conv);
		tmp += node->itemlen;
		node = node->next;
	}
	total = write(fd, dst, total);
	return (free(dst), ft_pflistclear(origin), total);
}
