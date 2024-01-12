/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printcomp_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:28:42 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/12 19:07:50 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <limits.h>

		// if (node->conv->conversion == 'c')
			
		// if (node->conv->conversion == 's')

		// if (node->conv->conversion == 'p')

		// if (node->conv->conversion == 'd')
//TODO: this pasting the conversions!
static void	pasteitem_helper(t_comp *node, char *tmp, int *itemlen, t_conv *conv)
{
	if (conv->conversion == '%')
		*tmp = '%'; 
	if (conv->conversion == 'c')
		*tmp = *(char *)node->item;
	if (conv->conversion == 's')
		
	if (conv->conversion == 'p')
	
	if (conv->conversion == 'd' || conv->conversion == 'i')
	
	if (conv->conversion == 'u')
	
	if (conv->conversion == 'o')
	
	if (conv->conversion == 'x')
	
	if (conv->conversion == 'X')
	
}

static void	pasteitem(t_comp *node, char *tmp, int *itemlen, t_conv *conv)
{
	if (node->conv && (node->conv->conversion == 'c'
		|| node->conv->conversion == '%' || node->conv->conversion == 's'))
	{
		if (!conv->minus && conv->fieldwidth > conv->arglength)
			//space/zero's.	positive fieldwidth
		if () 
			//zero's.			integer precision
		//item placing.		%cspdiuoxX
		pasteitem_helper(node, tmp, itemlen, conv);
		if (!conv->minus && conv->fieldwidth > conv->arglength)
			//space's.		negative fieldwidth.
		
	}
	else if (node->conv && node->conv->conversion)
	{
		
	}
	else
		while (*itemlen--)
			*(tmp + *itemlen) = *((char *)node->item + *itemlen)
}

//	Prints the whole linked list out by:
//		adding each node's length, then malloc()'s the str,
//		then parsing the nodes one by one into the malloc str.
//		then write()'s the malloc str.
int	ft_printf_printcomp(int fd, t_comp *origin)
{
	int		total;
	t_comp	*node;
	char 	*result;
	char 	*tmp;

	total = 0;
	node = origin;
	while (node)
	{
		if (node->itemlen == ERROR_FT_PRINTF)
			return (ERROR_FT_PRINTF);
		total += node->itemlen;
		node = node->next;
	}
	result = (char *)malloc(total * sizeof(char));
	tmp = result;
	node = origin;
	while (result && node)
	{
		pasteitem(node, tmp, &node->itemlen, node->conv);
		tmp += node->itemlen;
		node = node->next;
	}
	total = write(fd, result, total);
	return (ft_freecomp(origin), total);
}
