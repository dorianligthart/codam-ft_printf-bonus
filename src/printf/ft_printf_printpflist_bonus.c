/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pflist_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:28:42 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/26 03:14:47 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //ft_strchr(), ft_longlen(), ft_strlen(), ft_memcpy(),
				    	//ft_pflistclear(), and the t_pflist t_conv structs;
#include <stdlib.h> //malloc(), free();
#include <limits.h> //MIN_INT
#include <unistd.h> //write();

// expects node struct, see 'ft_printf_bonus.h';
// expects dst to be able to hold everything;
// expects node->conv->precision to be the amount
//	of zero's, not the initial flag integer;
// 		note: provide precision - arglen will round up to 0 zero's if negative;
// expects no flags in 'node->conv' to
//	be unnecessarily (in case of UB) or incorrectly set.
//
//TODO: paste arglen, paste zero's, then paste prefix: 
//		ORDER OF PASTING::
//			dst + prefixlen + zero's + arglen--;
//			dst + prefixlen + zero's--;
//			dst + prefixlen--;
static void	paste_digit(char *dst, t_pflist *node, char *basestr, char *prefix)
{
	t_conv			*c;
	unsigned long	b;
	int				prefix_len;
	int				arglen;

	c = node->conv;
	prefix_len = ft_strlen(prefix);
	b = ft_strlen(basestr);
	arglen = ft_longlen(*(long *)node->item, b);
	if (c->precision < 0)
		c->precision = 0;
	while (b > 1 && c->len--)
	{
		*(dst + c->precision + prefix_len + c->len)
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
static void	prefix_precisionzeros_integer(t_pflist *node, char *tmp, t_conv *c)
{
	if (ft_strchr("di", c->conv) && *(int *)node->item == INT_MIN)
		ft_memcpy(tmp, "-2147483648", 11);
	else if (ft_strchr("di", c->conv) && *(int *)node->item < 0)
	{
		*(int *)node->item *= -1;
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
// 	while (c->minus && c->fieldwidth > c->len)
// 		*(tmp + c->len + --c->fieldwidth) = ' ';
// 	while (!c->minus && c->fieldwidth > c->len)
// 		*(tmp + --c->fieldwidth) = ' ';
// 	if (*(unsigned int *)node->item && c->precision != 0) //weird edgecase!
// 		ft_ulongtostr(node, tmp, 0, "0x");
// 	return ;
// }
static void	pasteinteger(t_pflist *node, char *tmp, t_conv *c)
{
//	handles e.g. "ppzzaass" the ss part, reduces fieldwidth to use it as offset;
//	what did he sayyyy:
//		str char where: p = prefix_chars, z = zeros, a = arg_chars, s = spaces;
	while (c->minus && c->fw > c->len)
		*(tmp + c->fw--) = ' ';
	if (c->conv == 'p' && !(int *)node->item)
		ft_memcpy(*(tmp + c->fw), "(nil)", c->len);
	else if (c->fw > c->len)
		prefix_precisionzeros_integer(node, tmp + c->fw - c->len, c);
	else if (c->len)
		prefix_precisionzeros_integer(node, tmp, c);
	while (!c->minus && c->fw && c->zero) //TODO: %p check needed for fieldwidth zero or space printing???
		*(tmp + c->len + c->fw--) = (char)'0';
	while (!c->minus && c->fw && !c->zero)
		*(tmp + c->len + c->fw--) = (char)' ';
}

// order of node setting handling:
//	- format str;
//	- 1 char long + fw;
//	- char *str, strlen(str) or, if smaller, precision len + fw;
//	- digit conversion;
// pastes the string, character or percent_sign into tmp; or calls pasteitem2().
static void	pasteitem(t_pflist *node, char *tmp, t_conv *c)
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
		while (c->minus && c->fw-- >= c->len)
			*(tmp + c->len + c->fw) = ' ';
		while ((char *)node->item && c->len--)
			*(tmp + c->fw + c->len) = *(char *)node->item + c->len;
		if (!(char *)node->item)
			ft_memcpy(*(tmp + c->fw), "(null)", 6);		
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
int	ft_printf_printpflist(int fd, t_pflist *origin)
{
	int		total;
	t_pflist	*node;
	char	*result;
	char	*tmp;

	total = 0;
	node = origin;
	while (node)
	{
		if (node->itemlen == ERROR_LIBFT)
			return (ERROR_LIBFT);
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
	return (ft_pflistclear(origin), total);
}
