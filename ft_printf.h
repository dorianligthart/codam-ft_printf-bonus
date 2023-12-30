/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:34:14 by doligtha          #+#    #+#             */
/*   Updated: 2023/12/30 01:52:13 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>	//va_list, va_arg(), va_end()
# include <unistd.h>	//write()
# include <stdlib.h>	//malloc(), free()

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

//debug:
# include <stdio.h>
# include <fcntl.h>
# define ERRORMSG(x) \
	do {printf("%s:%d, %s: %s\n", __FILE__, __LINE__, __func__, #x);\
		exit(1);} while (0);

//WHOLE MANDATORY (and bonus) PROTOTYPE:
int		ft_printf(const char *format, ...)\
			__attribute__ ((format (printf, 1, 2)));

//BONUS UTILS:
typedef struct s_data
{
	int		minus;		//bool
	int		zero;		//bool
	int		hash;		//bool
	int		space;		//bool
	int		plus;		//bool
	int		width;		//field width (for everything, amount of space's)
	int		dot;		//bool
	int		precision;	//precision width (for integers, amount of zero's)
}	t_data;

//either:  t_comp.str or (t_comp.item + t_comp.data) exists. never both!
typedef struct s_comp
{
	int				len;
	const char		*formatsubstr;
	void			*item;
	t_data			*data;
	struct s_comp	*next;
}	t_comp;

int	print_comp(t_comp *origin)
{
	ERRORMSG("NOT IMPLEMENTED YET!");
	return (FALSE);
}
//new libft functions:
void	arg_array(int **table, const char *format, ...);

//old libft functions:
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);

#endif // FT_PRINTF_H