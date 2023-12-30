/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:57:05 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/29 21:57:32 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdarg.h>

typedef struct s_data
{
	int			minus;	//bool
	int			zero;	//bool
	int			hash;	//bool
	int			space;	//bool
	int			plus;	//bool
	int			width;	//int
	int			dot;	//bool
	int			precision; //int
}	t_data;

//ft_printf:
int		ft_printf(const char *f, ...) __attribute__ ((format (printf, 1, 2)));
// int		ft_printf(const char *format, ...);
int		ft_write_chr(int fd, char c, va_list *list, t_data *data);
int		ft_write_hex(int fd, char c, va_list *list, t_data *data);
int		ft_write_int(int fd, char c, va_list *list, t_data *data);
int		ft_write_oct(int fd, char c, va_list *list, t_data *data);
int		ft_write_ptr(int fd, char c, va_list *list, t_data *data);
int		ft_write_str(int fd, char c, va_list *list, t_data *data);
int		ft_write_uint(int fd, char c, va_list *list, t_data *data);

//libft:
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_ref_atoi(const char **nptr);
//new libft:
int		ft_putchr_repeat(int fd, int n, char *str);
int		ft_putulong(int fd, unsigned long nbr, char *basestr, int zeros);
int		ft_longlen(long n, long base);

#endif // FT_PRINTF_H
