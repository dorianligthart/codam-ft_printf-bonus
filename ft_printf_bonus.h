/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:34:14 by doligtha          #+#    #+#             */
/*   Updated: 2024/01/08 02:51:31 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>	//va_list, va_arg(), va_end()
# include <unistd.h>	//write()
# include <stdlib.h>	//malloc(), free()
# include <stdbool.h>	//'bool' variable type, true, false 

# ifndef ERROR_FT_PRINTF_BONUS
#  define ERROR_FT_PRINTF_BONUS -1
# endif

//DEBUG:
# include <stdio.h>
# include <fcntl.h>
# define ERRORMSG(x) do {\
		printf("%s:%d, %s: %s\n", __FILE__, __LINE__, __func__, #x);\
		exit(1);\
	} while (0);

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
typedef struct __attribute__((packed)) s_data
{
	bool	minus;
	bool	zero;
	bool	hash;
	bool	space;
	bool	plus;
	int		width;
	bool	dot;
	int		precision;
	char	conversion;
} 	t_data;  //15 bytes.

typedef struct __attribute__((packed)) s_comp
{
	int				len;
	void			*item;
	struct s_comp	*next;
}	t_comp; //20 bytes.

//new libft functions:
void	ft_arg_to_array(int **table, const char *format, ...);

//old libft functions:
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);

int		ft_printf_print_comp(t_comp **origin);
int		ft_printf_get_arg_len(t_comp *node, t_data *data, int len);
t_comp	*ft_newcomp_append(t_comp **comp);
t_data	*ft_newdata(void);
int		ft_printf(const char *format, ...) __attribute__((format (printf, 1, 2)));

#endif // FT_PRINTF_H
// // maybe union instead of 'void *item'?????????
// union item
// {
// 	char c;
// 	char *s;
// 	void *p;
// 	int d;
// 	int i;
// 	unsigned int u;
// 	unsigned int x;
// 	unsigned int X;
// 	unsigned int o;
// 	unsigned int %;
// }; //8 bytes
//len and item always exists.
