/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 23:55:22 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/30 17:29:08 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <fcntl.h>

#include <stdarg.h>

//sets &table[128]; index[format characters taken as integers] = va_list items.
void	arg_array(int **table, const char *format, ...)
{
	va_list		list;
	int			i;
	char		duptable[127];

	if (!format || !*format)
		return ;
	i = -1;
	while (++i < 128)
		duptable[i] = 0;
	i = -1;
	while (format && format[++i])
	{
		if (duptable[format[i]])
			return ;
		duptable[format[i]] = '_';
	}
	va_start(list, format);
	i = -1;
	while (format[++i])
		table[format[i]] = va_arg(list, void *);
	va_end(list);
}

// 	// int fd = open("test.txt", O_RDWR);
// 	// write(fd, table, 128);
// int main(void)
// {
// 	// return (0);
// 	int *letsgo[128];
// 	int a = 1;
// 	int b = 2;
// 	int c = 3;
// 	int d = 42;
// 	int e = 5;
// 	int f = 6;
// 	int g = 7;
// 	int h = 8;
// 	int i = 9;	
// 	char *format = "abcdefghi";
// 	arg_array(letsgo, format, &a, &b, &c, &d, &e, &f, &g, &h, &i);
// 	printf("MAIN a: %d\n", *letsgo['a']);
// 	printf("MAIN b: %d\n", *letsgo['b']);
// 	printf("MAIN c: %d\n", *letsgo['c']);
// 	printf("MAIN d: %d\n", *letsgo['d']);
// 	printf("MAIN e: %d\n", *letsgo['e']);
// 	printf("MAIN f: %d\n", *letsgo['f']);
// 	printf("MAIN g: %d\n", *letsgo['g']);
// 	printf("MAIN h: %d\n", *letsgo['h']);
// 	printf("MAIN i: %d\n", *letsgo['i']);

// 	// int iterate = 0;
// 	// while (iterate < 128)
// 	// {
// 	// 	if (!strchr(format, (char)iterate))
// 	// 		(*letsgo)[iterate] = 0;
// 	// 	if (*letsgo[iterate])
// 	// 		printf("%d=\t%d\n", iterate, *letsgo[iterate]);
// 	// 	iterate++;
// 	// }
// 	return 0;
// }
