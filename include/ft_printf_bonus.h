/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:34:14 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/11 20:08:41 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>	// va_list, va_arg(), va_end()
# include <unistd.h>	// write()
# include <stdlib.h>	// malloc(), free()
# include <stdbool.h>	// 'bool' variable type, true, false 

# ifndef ERROR_FT_PRINTF
#  define ERROR_FT_PRINTF -1
# endif

// DATA FOR PRINTF ARGUMENTS:
// bool minus		= flag.
// bool zero		= flag.
// bool hash		= flag.
// bool space		= flag.
// bool plus		= flag.
// int	width		= field width (for every conversion, the amount of space's).
// bool dot			= flag.
// int	precision	= precision width (for integers only, the amount of zero's).
// char conversion	= conversion, supported: c, s, p, d, i, u, x, X, %, o.
// 15bytes
typedef struct __attribute__((packed)) s_conv
{
	bool	minus;
	bool	zero;
	bool	hash;
	bool	space;
	bool	plus;
	int		fieldwidth;
	bool	dot;
	int		precision;
	char	conversion;
	int		arglength;
}	t_conv;

// linked list!
// 28 bytes.
typedef struct __attribute__((packed)) s_comp
{
	int				itemlen;
	void			*item;
	t_conv			*conv;
	struct s_comp	*next;
}	t_comp;

//new libft functions:
int		ft_longlen(long n, long base);
void	ft_arg_to_array(int **table, const char *format, ...);

//old libft functions:
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);

int		ft_printf_printcomp(int fd, t_comp *origin);
int		ft_printf_getitemlength(int conversion, void *item, t_conv *conv, int arglen);
int		ft_printf_getarglength(int conversion, void *item, t_conv *conv, int arglen);
t_comp	*ft_newcomp_append(t_comp **comp);
t_conv	*ft_newconv(void);
int		ft_printf(const char *format, ...)
		__attribute__((format (printf, 1, 2)));

#endif // FT_PRINTF_H
