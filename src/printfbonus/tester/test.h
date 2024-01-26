/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:26:28 by rde-brui          #+#    #+#             */
/*   Updated: 2024/01/26 01:05:48 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# ifndef SHOWCASE
#  define SHOWCASE false
# endif

# ifndef NIL
#  define NIL true
# endif

# ifndef NUM
#  define NUM false
# endif

# ifndef TEXT_ONLY
#  define TEXT_ONLY true
# endif

# include "libft.h"

# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <stdbool.h>

void	testing(short int test_index, const char *text, ...);
int		capture_output(int (*func)(const char *, va_list), char *output_buffer,
											const char *text, va_list start);

void	chr(void);
void	str(void);
void	integer(void);
void	unsigned_int(void);
void	small_x(void);
void	big_x(void);
void	void_ptr(void);
void	percentage_char(void);

void	chr_bns(void);
void	str_bns(void);

void	u_bns(void);
void	x_bns(void);
void	X_bns(void);
void	d_bns(void);
void	ptr_bns(void);

void	markup(char *str, ...);
void	print_full_width(const int c);
char	*tester_itoa(int n);
size_t	ft_strllcpy(char *dst, const char *src, size_t size);
#endif