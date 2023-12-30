/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:34:14 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/30 17:39:15 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>	//va_list, va_arg(), va_end()
# include <unistd.h>	//write()
# include <stdlib.h>	//malloc(), free()
# include <stdbool.h>	//'bool' variable type, TRUE, FALSE

# ifndef ERROR_FT_PRINTF
#  define ERROR_FT_PRINTF -1
# endif

//DEBUG:
# include <stdio.h>
# include <fcntl.h>
# define ERRORMSG(x) do {\
		printf("%s:%d, %s: %s\n", __FILE__, __LINE__, __func__, #x);\
		exit(1);\
	} while (0);

//WHOLE MANDATORY (and bonus) PROTOTYPE:
int		ft_printf(const char *format, ...)\
			__attribute__ ((format (printf, 1, 2)));

//BONUS UTILS:
//	mode		= conversion character from format string
//	minus		= bool flag
//	zero		= bool flag
//	hash		= bool flag
//	space		= bool flag
//	plus		= bool flag
//	width		= field width (for everything, amount of space's)
//	dot			= bool flag
//	precision	= precision width (for integers, amount of zero's)
typedef struct s_data //16 bytes
{
	char	conversion;	// 1 byte
	bool	minus;		// 1 byte
	bool	zero;		// 1 byte
	bool	hash;		// 1 byte
	bool	space;		// 1 byte
	bool	plus;		// 1 byte
	bool	dot;		// 1 byte
	int		width;		// 4 bytes
	int		precision;	// 4 bytes
}	t_data;

//len and item always exists.
typedef struct s_comp
{
	int				len;	//4 bytes
	void			*item;	//8 bytes
	t_data			data;	//16 bytes
	struct s_comp	*next;	//8 bytes
}	t_comp; //36 bytes total

int	ft_get_arg_len(t_comp *object);
int	ft_print_comp(t_comp *origin);

//new libft functions:
void	arg_array(int **table, const char *format, ...);

//old libft functions:
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);

#endif // FT_PRINTF_H