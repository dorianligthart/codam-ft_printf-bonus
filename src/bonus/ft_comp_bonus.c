/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comp_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:28:42 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/19 07:40:24 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include <limits.h>

// expects node struct, see 'ft_printf_bonus.h';
// expects dst to be able to hold everything;
// expects node->conv->precision to be the amount of zero's,
//		not the initial flag integer;
//	- note: provide precision - arglen will round up to 0 zero's if negative;
//
// expects no flags in 'node->conv' to be unnecessarily or incorrectly set.
static void	paste_digit(char *dst, t_comp *node, char *basestr, char *prefix)
{
	unsigned long	b;
	int				prefix_len;

	if (node->conv->precision < 0)
		node->conv->precision = 0;
	b = ft_strlen(basestr);
	prefix_len = ft_strlen(prefix);
	while (b > 1 && !ft_strchr("di", node->conv->conv) && node->conv->len--)
	{
		*(dst + node->conv->precision + prefix_len + node->conv->len)
			= basestr[(unsigned long)node->item % b];
		(unsigned long)node->item / b;
	}
	while (b > 1 && ft_strchr("di", node->conv->conv) && node->conv->len--)
	{
		*(dst + node->conv->precision + prefix_len + node->conv->len)
			= basestr[(int)node->item % 10
				* (((int)node->item < 0) * -2 + 1) + '0'];
		(int)node->item / b;
	}
	while (node->conv->precision--)
		*(dst + node->conv->precision) = '0';
	while (prefix_len--)
		*(dst + node->conv->precision + prefix_len) = prefix[prefix_len];
}

//before everything p exception. dont know if I need this:
// if (c->conv == 'p')
// {
// 	while (c->minus && c->fieldwidth > c->len)
// 		*(tmp + c->len + --c->fieldwidth) = ' ';
// 	while (!c->minus && c->fieldwidth > c->len)
// 		*(tmp + --c->fieldwidth) = ' ';
// 	if (*(unsigned int *)node->item && c->precision != 0) //weird edgecase!
// 		ft_ulongtostr(node, tmp, 0, "0x");
// 	return ;
// }
static void	pasteitem2(t_comp *node, char *tmp, t_conv *c)
{
	node->itemlen
		= c->precision * (c->precision > -1 && c->precision < c->len)
		+ c->len * (c->precision == -1 || c->precision >= c->len);
	c->precision = c->precision - c->len;
	while (c->minus && c->fieldwidth > node->itemlen)
		*(tmp + c->fieldwidth--) = ' ';
	paste_digit(tmp, node,
		((c->conv == 'd' || c->conv == 'i' || c->conv == 'u')
			* (unsigned long)"0123456789")
		+ ((c->conv == 'x' || c->conv == 'p')
			* (unsigned long)"0123456789abcdef")
		+ ((c->conv == 'X') * (unsigned long)"0123456789ABCDEF")
		+ ((c->conv == 'o') * (unsigned long)"01234567"),
		((c->conv == 'd' || c->conv == 'i') * (c->space) * (unsigned long)" ")
		+ ((c->conv == 'd' || c->conv == 'i') * (c->plus) * (unsigned long)"+")
		+ ((c->conv == 'd' || c->conv == 'i')
			* ((int)node->item < 0) * (unsigned long)"-")
		+ (((c->conv == 'x') * (c->hash) || c->conv == 'p')
			* (unsigned long)"0x")
		+ ((c->conv == 'X') * (c->hash) * (unsigned long)"0X")
		+ ((c->conv == 'o') * (c->hash) * (unsigned long)"0"));
	while (!c->minus && c->fieldwidth > node->itemlen)
		*(tmp + node->itemlen + c->fieldwidth--)
			= (c->zero && c->conv != 'p') * (unsigned long)"0"
			+ (!c->zero || c->conv == 'p') * (unsigned long)" ";
}

// order of node setting handling:
//	- format str;
//	- 1 char long + fieldwidth;
//	- char *str, strlen(str) or, if smaller, precision len + fieldwidth;
//	- digit conversion;
// pastes the string, character or percent_sign into tmp; or calls pasteitem2().
static void	pasteitem(t_comp *node, char *tmp, t_conv *c)
{
	if (!c->conv)
		while (node->itemlen--)
			*(tmp + node->itemlen) = *((char *)node->item + node->itemlen);
	else if (c->conv == 'c' || c->conv == '%')
	{
		while (c->minus && c->fieldwidth > c->len)
			*(tmp + c->len + c->fieldwidth--) = ' ';
		*((char *)node->item + c->fieldwidth) = (char)c->conv;
		while (!c->minus && c->fieldwidth > c->len)
			*(tmp + c->len + c->fieldwidth--) = ' ';
	}
	else if (c->conv == 's')
	{
		if (c->len > c->precision)
			c->len = c->precision;
		while (c->minus && c->fieldwidth-- >= c->len)
			*(tmp + c->len + c->fieldwidth) = ' ';
		c->fieldwidth -= c->len;
		while (c->len--)
			*(tmp + c->fieldwidth + c->len) = *(char *)node->item + c->len;
		while (!c->minus && c->fieldwidth--)
			*(tmp + c->fieldwidth) = ' ';
	}
	else if (ft_strchr("diuxXo", c->conv))
		pasteitem2(node, tmp, c);
}

//	Prints the whole linked list out by:
//		adding each node's len to total, then malloc(total),
//		then parsing the nodes one by one into the malloced str.
//		then write(fd, str, total).
int	ft_printf_printcomp(int fd, t_comp *origin)
{
	int		total;
	t_comp	*node;
	char	*result;
	char	*tmp;

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
		pasteitem(node, tmp, node->conv);
		tmp += node->itemlen;
		node = node->next;
	}
	total = write(fd, result, total);
	return (ft_freecomp(origin), total);
}
