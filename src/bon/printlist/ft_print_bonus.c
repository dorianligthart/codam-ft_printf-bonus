/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:28:42 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/02 04:11:59 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h" //ft_strchr(), ft_longlen(), ft_strlen(), ft_memcpy(),
				    	//ft_pflistclear(), and the t_pflist t_conv structs;
#include <stdlib.h> //malloc(), free();
#include <limits.h> //MIN_INT
#include <unistd.h> //write();

#ifndef DEBUG
// expects node struct, see 'ft_printf_bonus.h';
// expects dst to be able to hold everything;
// expects node->conv->precision to be the amount
//	of zero's, not the initial flag integer;
// 		note: provide precision - arglen will round up to 0 zero's if negative;
// expects no flags in 'node->conv' to
//	be unnecessarily (in case of UB) or incorrectly set.
//

//		ORDER OF PASTING::
//			dst + prefixlen + zero's + arglen--;
//			dst + prefixlen + zero's--;
//			dst + prefixlen--;
static void	paste_digit(char *dst, t_pflist *node, char *basestr, char *prefix)
{
	t_pfconv		*c;
	unsigned long	b;
	int				prefix_len;
	int				arglen;

	c = node->conv;
	prefix_len = ft_strlen(prefix);
	b = ft_strlen(basestr);
	arglen = ft_longlen(*(long *)node->item, b);
	if (c->precision < 0)
		c->precision = 0;
	while (b > 1 && c->arglen--)
	{
		*(dst + c->precision + prefix_len + c->arglen)
			= basestr[(*(unsigned long *)node->item) % b];
		*(int *)node->item /= b;
	}
	while (c->precision--)
		*(dst + c->precision) = '0';
	while (prefix_len--)
		*(dst + c->precision + prefix_len) = prefix[prefix_len];
}


// calls paste_digit() with appropriate arguments (from t_pflist node info) to
//	paste: (prefix + zero's + integer) onto tmp.
static void	prefix_precisionzeros_integer(t_pflist *node, char *tmp,
											t_pfconv *c)
{
	if (ft_strchr("di", c->conv) && node->item.i == INT_MIN)
		ft_memcpy(tmp, "-2147483648", 11);
	else if (ft_strchr("di", c->conv) && node->item.i < 0)
	{
		node->item.i *= -1;
		paste_digit(tmp, node, "0123456789", "-");
	}
	else if (ft_strchr("di", c->conv) && c->plus)
		paste_digit(tmp, node, "0123456789", "+");
	else if (ft_strchr("di", c->conv) && c->space)
		paste_digit(tmp, node, "0123456789", " ");
	else if (ft_strchr("di", c->conv))
		paste_digit(tmp, node, "0123456789", "");
	else if (c->conv == 'u')
		paste_digit(tmp, node, "0123456789", "");
	else if (c->conv == 'p' || (c->conv == 'x' && c->hash))
		paste_digit(tmp, node, "0123456789abcdef", "0x");
	else if (c->conv == 'x' && !c->hash)
		paste_digit(tmp, node, "0123456789abcdef", "");
	else if (c->conv == 'X' && c->hash)
		paste_digit(tmp, node, "0123456789ABCDEF", "0X");
	else if (c->conv == 'X' && !c->hash)
		paste_digit(tmp, node, "0123456789ABCDEF", "");
}

//before everything p exception. dont know if I need this:
// if (c->conv == 'p')
// {
// 	while (c->minus && c->fieldwidth > c->arglen)
// 		*(tmp + c->arglen + --c->fieldwidth) = ' ';
// 	while (!c->minus && c->fieldwidth > c->arglen)
// 		*(tmp + --c->fieldwidth) = ' ';
// 	if (*(unsigned int *)node->item && c->precision != 0) //weird edgecase!
// 		ft_ulongtostr(node, tmp, 0, "0x");
// 	return ;
// }
static void	pasteinteger(t_pflist *node, char *tmp, t_pfconv *c)
{
	while (c->minus && c->fw > c->arglen)
		*(tmp + c->fw--) = ' ';
	if (c->conv == 'p' && !node->item.ptr)
		ft_memcpy(tmp + c->fw, "(nil)", 5);
	else if (c->fw > c->arglen)
		prefix_precisionzeros_integer(node, tmp + c->fw - c->arglen, c);
	else if (c->arglen)
		prefix_precisionzeros_integer(node, tmp, c);
	while (!c->minus && c->fw && c->zero) //TODO: %p check needed for fieldwidth zero or space printing???
		*(tmp + c->arglen + c->fw--) = (char)'0';
	while (!c->minus && c->fw && !c->zero)
		*(tmp + c->arglen + c->fw--) = (char)' ';
}

static void	paste_actual_item(union s_pfitem *item, int arglen, char c)
{
	
}

// order of node setting handling:
//	- format str;
//	- 1 char long + fw;
//	- char *str, strlen(str) or, if smaller, precision len + fw;
//	- digit conversion;
// pastes the string, character or percent_sign into tmp; or calls pasteitem2().
static void	pasteitem(t_pflist *node, char *tmp, t_pfconv *c)
{
	while (c == NULL && node->itemlen--)
		*(tmp + node->itemlen) = *(node->item.s + node->itemlen);
	if (c->conv == 'c' || c->conv == '%')
	{
		while (c->minus && c->fw > c->arglen)
			*(tmp + c->arglen + c->fw--) = ' ';
		*(tmp + c->fw - c->arglen) = '%';
		if (c->conv == 'c')
			*(tmp + c->fw - c->arglen) = node->item.c;
		while (!c->minus && c->fw > c->arglen)
			*(tmp + c->arglen + c->fw--) = ' ';
	}
	// else if (c->conv == 's')
	// {
	// 	while (c->minus && c->fw-- >= c->arglen)
	// 		*(tmp + c->arglen + c->fw) = ' ';
	// 	while (node->item.s && c->arglen--)
	// 		*(tmp + c->fw + c->arglen) = *(node->item.s + c->arglen);
		if (!node->item.s)
			ft_memcpy(tmp + c->fw, "(null)", 6);
	// 	while (!c->minus && c->fw--)
	// 		*(tmp + c->fw) = ' ';
	// }
	else if (ft_strchr("pdiuxXo", c->conv))
		pasteinteger(node, tmp, c);
}

//	Prints the whole linked list out by:
//		adding each node's len to total, then malloc(total),
//		then parsing the nodes one by one into the malloced str.
//		then write(fd, str, total).
int	ft_printf_printpflist(int fd, t_pflist *origin, int total)
{
	t_pflist	*node;
	char		*result;
	char		*tmp;

	node = origin;
	while (node)
	{
		if (node->itemlen == ERROR_FTPRINTF)
			return (ft_pflistclear(origin), ERROR_FTPRINTF);
		total += node->itemlen;
		node = node->next;
	}
	result = (char *)malloc(total * sizeof(char));
	tmp = result;
	node = origin;
	while (result && node)
	{
		pasteitem(node, tmp, node->conv);
		tmp += node->itemlen;
		node = node->next;
	}
	total = write(fd, result, total);
	return (free(result), ft_pflistclear(origin), total);
}
#else	//ifndef DEBUG
int	ft_printf_printpflist(int fd, t_pflist *origin, int i)
{
	t_pflist	*ptr;

	ptr = origin;
	while (ptr)
	{
		if (i != 0)
			printf(",");
		printf("\n");
		printf(GREEN"\tnode_%p: {\n"RESET, ptr);
			printf(MAGENTA"\t\t.item: %p,\n"RESET, &ptr->item);
			if (ptr->conv)
			{
				printf(MAGENTA"\t\t.conv_%p: [\n"RESET, ptr->conv);
					printf("\t\t\t.minus:      "CYAN"%s"RESET",\n", ptr->conv->minus ? "true" : "false");
					printf("\t\t\t.zero:       "CYAN"%s"RESET",\n", ptr->conv->zero ? "true" : "false");
					printf("\t\t\t.hash:       "CYAN"%s"RESET",\n", ptr->conv->hash ? "true" : "false");
					printf("\t\t\t.space:      "CYAN"%s"RESET",\n", ptr->conv->space ? "true" : "false");
					printf("\t\t\t.plus:       "CYAN"%s"RESET",\n", ptr->conv->plus ? "true" : "false");
					printf("\t\t\t.fieldwidth: "CYAN"%d"RESET",\n", ptr->conv->fw);
					printf("\t\t\t.dot:        "CYAN"%s"RESET",\n", ptr->conv->dot ? "true" : "false");
					printf("\t\t\t.precision:  "CYAN"%d"RESET",\n", ptr->conv->precision);
					printf("\t\t\t.lengthmod:  "CYAN"%d"RESET",\n", ptr->conv->lengthmod);
					printf("\t\t\t.conv: "CYAN"%c"RESET",\n", ptr->conv->conv);
					printf("\t\t\t.arglen:        "CYAN"%d"RESET",\n", ptr->conv->arglen);
				printf(MAGENTA"\t\t],\n"RESET);
			}
			printf(MAGENTA"\t\t.itemlen: %d,\n"RESET, ptr->itemlen);
			printf(MAGENTA"\t\t.next: %p\n"RESET, ptr->next);
		printf(GREEN"\t}"RESET);
		ptr = ptr->next;
		i++;
	}
	return (ft_pflistclear(origin), fd - 1 + i);
}
#endif	//ifndef DEBUG
