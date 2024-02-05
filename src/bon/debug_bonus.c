/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:28:42 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 01:11:11 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h" //ft_strchr(), ft_longlen(), ft_strlen(), ft_memcpy(),
				    	//ft_pflistclear(), and the t_pflist t_conv structs;
#include <stdlib.h> //malloc(), free();
#include <limits.h> //MIN_INT
#include <unistd.h> //write();

void	ft_pf_viewnode(t_pflist *node)
{
printf(GREEN"\tnode_%p: {\n"RESET, ptr);
	printf(MAGENTA"\t\t.item: %p,\n"RESET, &node->item);
	if (node->conv)
	{
		printf(MAGENTA"\t\t.conv_%p: [\n"RESET, node->conv);
			printf("\t\t\t.minus:      "CYAN"%s"RESET",\n", node->conv->minus ? "true" : "false");
			printf("\t\t\t.zero:       "CYAN"%s"RESET",\n", node->conv->zero ? "true" : "false");
			printf("\t\t\t.hash:       "CYAN"%s"RESET",\n", node->conv->hash ? "true" : "false");
			printf("\t\t\t.space:      "CYAN"%s"RESET",\n", node->conv->space ? "true" : "false");
			printf("\t\t\t.plus:       "CYAN"%s"RESET",\n", node->conv->plus ? "true" : "false");
			printf("\t\t\t.fieldwidth: "CYAN"%d"RESET",\n", node->conv->fw);
			printf("\t\t\t.dot:        "CYAN"%s"RESET",\n", node->conv->dot ? "true" : "false");
			printf("\t\t\t.precision:  "CYAN"%d"RESET",\n", node->conv->precision);
			printf("\t\t\t.lengthmod:  "CYAN"%d"RESET",\n", node->conv->lengthmod);
			printf("\t\t\t.c:          "CYAN"%c"RESET",\n", node->conv->c);
			printf("\t\t\t.arglen:     "CYAN"%d"RESET",\n", node->conv->arglen);
		printf(MAGENTA"\t\t],\n"RESET);
	}
	printf(MAGENTA"\t\t.itemlen: %d,\n"RESET, node->itemlen);
	printf(MAGENTA"\t\t.next: %p\n"RESET, node->next);
printf(GREEN"\t}"RESET);
}

// print whole ft_printf()'s linked list out.
int	ft_pf_viewpflist(t_pflist *origin)
{
	t_pflist	*ptr;
	int			i

	i = 0;
	ptr = origin;
	while (ptr)
	{
		if (i != 0)
			printf(",");
		printf("\n");
		ft_pf_viewnode(ptr);
		i++;
		ptr = ptr->next;
	}
	ft_pflistclear(origin);
	return (i);
}
