/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dligthar <dligthar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 14:30:54 by dligthar      #+#    #+#                 */
/*   Updated: 2023/03/26 20:21:25 by dligthar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//testing libs/references:
// https://en.cppreference.com/w/c/io/fprintf
// https://csnotes.medium.com/ft-printf-tutorial-42project-f09b6dc1cd0e
#include <stdio.h>

//real:
#include "../ft_printf.h"

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/*

*/
typedef struct	s_print
{
	va_list	args;
	int		hash; //flag
	int		zero; //flag
	int		dash; //flag
	int		spce; //flag
	int		plus; //flag
	int		fieldwidth; //decimal
	int		dot;
	int		precision;
	int		lengthmod;
}				t_print;

t_print	*ft_tabnew(t_print *tab)
{
	tab->;
	tab->;
	tab->;
	tab->;
	tab->;
	tab->;
	return (tab);
}

//fs = format specifier.
int		ft_printf_fs_parse(const char *format, char id)
{
	
}

int		ft_vprintf(const char *format, va_list vlist) // "cspdiuxX%"
{
	int		i;
	// int		hash; // '#'
	// int		dash; // '-'
	// int		zero; // '0'
	// int		plus; // '+'
	// int		empt; // ' '

	if (ft_printf_strchr(format, 'c'))
	if (ft_printf_strchr(format, 's'))
	if (ft_printf_strchr(format, 'p'))
	if (ft_printf_strchr(format, 'd'))
	if (ft_printf_strchr(format, 'i'))
	if (ft_printf_strchr(format, 'u'))
	if (ft_printf_strchr(format, 'x'))
	if (ft_printf_strchr(format, 'X'))
	if (ft_printf_strchr(format, '%'))
		write(1, "%", 1);
	

	if (ft_printf_strchr(format, '-'))
		i = ft_printf_fs_parse(format, '-');
	else if (ft_printf_strchr(format, '0'))
		i = ft_printf_fs_parse(format, '0');
	else if (ft_printf_strchr(format, ' '))
		i = ft_printf_fs_parse(format, ' ');
		
	if (ft_printf_strchr(format, '#')
		&& ((ft_printf_strchr(format, 'x') || ft_printf_strchr(format, 'X'))))
		write(1, ft_itoa_base(va_arg(vlist, int), 10), ft_intlen(va_arg(vlist, int)));
	return (i);
}

/*
format: "%[Flags][Field Width][Precision]{format}"
	Flags: 			'#-+ 0';
	Field Width:	[int];
	Precision:		['.[int]']; defaults to '.0' if 'int' isn't given;
	format:			'cspdiuxX%';
fs_len = format specifier str length from char AFTER initial '%'. "%#123.456dddddddddd" returns strlen 9.
*/
int		ft_printf_fs_len(const char *format)
{
	int		m;

	m = 1;
	while (ft_strchr("#-+ 0", format[m]))
		m++;
	if (format[m] >= '1' && format[m] <= '9')
		m++;
	while (format[m] >= '0' && format[m] <= '9')
		m++;
	if (format[m] == '.')
		m++;
	while (format[m] >= '0' && format[m] <= '9')
		m++;
	if (!ft_strchr("cspdiuxX%", format[m]))
		return (-1);
	return (m + 1);
}

/*
format: "%[Flags][Field Width][Precision]{format}"
	Flags: 			'#-+ 0';
	Field Width:	[int];
	Precision:		['.[int]']; defaults to '.0' if 'int' isn't given;
	format:			'cspdiuxX%';
fs_mode
*/
int		ft_printf_flag_mode(const char *format)
{
	int		m;

	m = 1;
	while (ft_strchr("#-+ 0", format[m]))
		m++;
	if (format[m] >= '1' && format[m] <= '9')
		m++;
	while (format[m] >= '0' && format[m] <= '9')
		m++;
	if (format[m] == '.')
		m++;
	while (format[m] >= '0' && format[m] <= '9')
		m++;
	if (!ft_strchr("cspdiuxX%", format[m]))
		return (-1);
	return (m + 1);
}

/*
Description:
A function that will mimic the original printf().
Supported formats: "%c, %s, %p, %d, %i, %u, %x, %X and %%",

format structure (in this order): %[Flags][Field Width][Precision]{format}
- Flags:
	Info:
	'#' = "alternate form". For format 'cspdiu%' this option is ignored.
		For 'xX' will prefix the digit with '0x' or '0X' respectively.
	'-' = Specifies left adjustment of the output in the indicated field;
	'0' = Specifying that zero-padding should be used rather than blank-padding;
	'+' = Specifying that there should always be a '+' placed before the number when using signed formats;
	' ' = Specifying that a blank should be left before a positive number for a signed format.
		lowest padding and symbol rank. If [Field Width] isn't provided it defaults to intlen + 1;
	Padding hierarchy:
	'-' overwrites '0' and ' ';
	'0' overwrites ' ';
	Signed Symbol hierarchy:
	'+' overwrites ' ';
- Field Width:
	An optional digit string specifying a field width; if the output string has fewer bytes than the 
	field width it will be blank-padded on the left (or right if '-') to make up the field width.
	(note difference between leading 0 and embedded 0).
- Precision:
	An optional period, `.', followed by an optional [digit string], is the maximum number of bytes 
	to be printed from a string (format: s); if no digit is provided, the precision is treated as zero;
- format ("cspdiuxX%"):
	'diuxX'	= The argument is printed as a signed decimal (d or i), unsigned decimal (u),
			or unsigned hexadecimal (x or X) where ``abcdef'' and ``ABCDEF'' are used respectively.
	'c'		= The first byte of argument is printed.
	's'		= Bytes from the string argument are printed until the end is reached or until the number of
			bytes indicated by the precision specification is reached; however if the precision is 0
			or missing, the string is printed entirely.
	'p'		= The void * pointer argument is printed in hexadecimal (as if by '%#x')
	'%'		= A '%' is written.  No argument is converted.
*/
int		ft_printf(const char *format, ...)
{
	va_list	vlist;
	int		i;
	int		i_skip;
	int		len;

	va_start(vlist, format);
	i = 0;
	len = 0;
	while (format && format[i])
	{
		if (format[i] == '%')
		{
			i_skip = ft_printf_fs_len(format + i);
			if (!i_skip)
				return (0);
			len += ft_vprintf(format + i, vlist); //"123456%s7890", "abc" len = 3
			i += i_skip;
		}
		else
			write(1, format[i], 1);
		i++;
		len++;
	}
	va_end(vlist);
	return (len);
}

int main(int argc, char const *argv[])
{
	int		a = 10;
	int		p = &a;

	ft_printf("[test 1] %c\n", "c");
	ft_printf("[test 2] %s\n", "12345\n67890");
	ft_printf("[test 3] %p\n", p);
	ft_printf("[test 4] %d\n", a);
	ft_printf("[test 5] %i\n", a);
	ft_printf("[test 6] %u\n", a);
	ft_printf("[test 7] %x\n", 10);
	ft_printf("[test 8] %X\n", 10);
	ft_printf("[test 9] %%\n");

	printf("%#01293.232%", 'p');
	return (0);
}
