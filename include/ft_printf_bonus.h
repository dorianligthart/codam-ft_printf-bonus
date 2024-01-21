/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:34:14 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/21 18:41:26 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

//STD libs:
# include <stdarg.h>	// va_list, va_arg(), va_end()
# include <unistd.h>	// write()
# include <stdlib.h>	// malloc(), free()
# include <stdbool.h>	// 'bool' variable type, true, false

# include "libft.h"
// void	*ft_memcpy(void *dest, const void *src, size_t n)
// int	ft_atoi(const char *nptr)
// char	*ft_strchr(const char *s, int c)
// size_t	ft_strlen(const char *s)

# ifndef ERROR_FT_PRINTF
#  define ERROR_FT_PRINTF -1
# endif

// 19 bytes -> 20
typedef struct s_conv
{
	bool	minus;
	bool	zero;
	bool	hash;
	bool	space;
	bool	plus;
	int		fw;
	bool	dot;
	int		precision;
	char	conv;
	int		len;
}	t_conv;

// linked list :D!
// 28 bytes -> 32 bytes
typedef struct s_comp
{
	void			*item;
	t_conv			*conv;
	int				itemlen;
	struct s_comp	*next;
}	t_comp;

//new libft functions:
int		ft_longlen(long n, long base);
void	ft_varray(char **array, const char *format, ...);

//old libft functions:
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);

//ft_printf:
int		ft_printf_printcomp(int fd, t_comp *origin);
int		ft_printf_getitemlength(int conversion, void *item, t_conv *conv);
int		ft_printf_getarglength(int conversion, void *item);

//structs:
void	ft_compclear(t_comp *comp);
t_comp	*ft_newcomp_append(t_comp **comp);
t_conv	*ft_newconv(void);
int		ft_printf(const char *format, ...)
		__attribute__((format (printf, 1, 2)));

#endif // FT_PRINTF_H
