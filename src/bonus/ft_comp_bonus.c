/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comp_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:28:42 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/20 20:51:42 by doligtha         ###   ########.fr       */
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
	t_conv			*c;
	unsigned long	b;
	int				prefix_len;

	prefix_len = ft_strlen(prefix);
	b = ft_strlen(basestr);
	c = node->conv;
	if (c->precision < 0)
		c->precision = 0;
	while (b > 1 && c->len--)
	{
		*(dst + c->precision + prefix_len + c->len)
			= basestr[(*(unsigned long *)node->item) % b];
		(int)node->item / b;
	}
	while (c->precision--)
		*(dst + c->precision) = '0';
	while (prefix_len--)
		*(dst + c->precision + prefix_len) = prefix[prefix_len];
}

void	paste_prefix_precisionzeros_integer(t_comp *node, char *tmp, t_conv *c)
{
	if (c->conv == 'd' || c->conv == 'i')
	{
		if (*(int *)node->item == INT_MIN)
			ft_memcpy(tmp, "-2147483648", 11);
		else if (*(int *)node->item < 0)
		{
			*(int *)node->item *= -1;
			paste_digit(tmp, node, "0123456789", "-");
		}
		else if (*(int *)node->item >= 0 && (c->space || c->plus))
			paste_digit(tmp, node, "0123456789",\
				c->space * (long)" " + c->plus * (long)"+");
		else if (*(int *)node->item >= 0)
			paste_digit(tmp, node, "0123456789", "");
	}
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
// 	while (c->minus && c->fieldwidth > c->len)
// 		*(tmp + c->len + --c->fieldwidth) = ' ';
// 	while (!c->minus && c->fieldwidth > c->len)
// 		*(tmp + --c->fieldwidth) = ' ';
// 	if (*(unsigned int *)node->item && c->precision != 0) //weird edgecase!
// 		ft_ulongtostr(node, tmp, 0, "0x");
// 	return ;
// }
static void	pasteinteger(t_comp *node, char *tmp, t_conv *c)
{
	// if (c->precision > -1 && c->precision < c->len)
	// 	c->precision
	// node->itemlen
	// 	= c->precision * (c->precision > -1 && c->precision < c->len)
	// 	+ c->len * (c->precision == -1 || c->precision >= c->len);

	// ????? im skeptical :////
	c->precision = c->precision - c->len;
	while (c->minus && c->fw > node->itemlen)
		*(tmp + c->fw--) = ' ';
	paste_prefix_precisionzeros_integer(node, tmp + c->fw, c);
	while (!c->minus && c->fw > node->itemlen)
		*(tmp + node->itemlen + c->fw--)
			= (c->zero && c->conv != 'p') * (unsigned long)"0"
			+ (!c->zero || c->conv == 'p') * (unsigned long)" ";
}

// order of node setting handling:
//	- format str;
//	- 1 char long + fw;
//	- char *str, strlen(str) or, if smaller, precision len + fw;
//	- digit conversion;
// pastes the string, character or percent_sign into tmp; or calls pasteitem2().
static void	pasteitem(t_comp *node, char *tmp, t_conv *c)
{
	while (!c->conv && node->itemlen--)
		*(tmp + node->itemlen) = *((char *)node->item + node->itemlen);
	if (c->conv == 'c' || c->conv == '%')
	{
		while (c->minus && c->fw > c->len)
			*(tmp + c->len + c->fw--) = ' ';
		*((char *)node->item + c->fw) = (char)((c->conv == '%') * '%'
			+ (c->conv == 'c') * (int)(*(char *)node->item));
		while (!c->minus && c->fw > c->len)
			*(tmp + c->len + c->fw--) = ' ';
	}
	else if (c->conv == 's')
	{
		if (c->len > c->precision)
			c->len = c->precision;
		while (c->minus && c->fw-- >= c->len)
			*(tmp + c->len + c->fw) = ' ';
		c->fw -= c->len;
		while (c->len--)
			*(tmp + c->fw + c->len) = *(char *)node->item + c->len;
		while (!c->minus && c->fw--)
			*(tmp + c->fw) = ' ';
	}
	else if (ft_strchr("diuxXo", c->conv))
		pasteinteger(node, tmp, c);
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
	return (ft_compclear(origin), total);
}
