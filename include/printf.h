/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:22:38 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/02 04:04:20 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# ifdef DEBUG
#  include <stdio.h>
#  include <unistd.h>
#  include <limits.h>
#  include <string.h>
#  if defined(RESET) || defined(BLACK) || defined(RED) \
	|| defined(GREEN) || defined(YELLOW) || defined(BLUE) \
	|| defined(MAGENTA) || defined(CYAN) || defined(WHITE)
#  else
#   define RESET "\033[0m"
#   define BLACK "\033[0;30m"
#   define RED "\033[0;31m"
#   define GREEN "\033[0;32m"
#   define YELLOW "\033[0;33m"
#   define BLUE "\033[0;34m"
#   define MAGENTA "\033[0;35m"
#   define CYAN "\033[0;36m"
#   define WHITE "\033[0;37m"
#  endif // #ifndef COLOR_NAMES
# endif // #ifdef DEBUG

#  ifndef ERROR_FTPRINTF
#   define ERROR_FTPRINTF -1
#  endif

#  include <stdbool.h>
#  include <stdarg.h>
#  include <stdint.h>
#  include <stddef.h>
#  include <sys/types.h>

union s_pfitem
{
	char 				c;
	char * 				s;

	signed char			hhi;
	short				hi;
	int					i;
	long				li;
	long long			lli;
	intmax_t			ji;
	ssize_t				zi;
	ptrdiff_t			ti;

	unsigned char		hhu;
	unsigned short		hu;
	unsigned int		u;
	unsigned long		lu;
	unsigned long long	llu;
	uintmax_t			ju;
	size_t				zu;
	ptrdiff_t			tu;

	double				f;
	long double			Lf;

	signed char	*		hhn;
	short *				hn;
	int *				n;
	long *				ln;
	long long *			lln;
	intmax_t *			jn;
	size_t *			zn;
	ptrdiff_t *			tn;

	void *				p;
};

//lengthmod:
// 0 == none;
// 1 == h;
// 2 == l;
// 3 == hh;
// 4 == ll;
// 5 == j;
// 6 == z;
// 7 == t;
// 8 == L;
typedef struct s_pfconv 
{
	bool	minus;
	bool	zero;
	bool	hash;
	bool	space;
	bool	plus;
	int		fw;
	bool	dot;
	int		precision;
	int		lengthmod;
	char	conv;
	int		arglen;
}	t_pfconv;

typedef struct s_pflist
{
	int				uniontype;
	union s_pfitem	item;
	t_pfconv		*conv;
	int				itemlen;
	struct s_pflist	*next;
}	t_pflist;

void		ft_pflistclear(t_pflist *pflist);
int			ft_printf_printpflist(int fd, t_pflist *origin, int total);

void		ft_pf_union(union s_pfitem *item, t_pfconv *conv, va_list *list);
int			ft_pf_arglen(union s_pfitem *item, t_pfconv *conv);
int			ft_pf_itemlen(union s_pfitem *item, t_pfconv *conv);

t_pfconv	*ft_newpfconv(void);
t_pflist	*ft_newpflist_append(t_pflist **pflist);

int			ft_printf(const char *format, ...) \
			__attribute__((format (printf, 1, 2)));

//TODO: integer viewed as characters, return strlen() functions:
/*
char
char *
signed char
short
int
long
long long
intmax_t
size_t
ptrdiff_t
unsigned char
unsigned short
unsigned int
unsigned long
unsigned long long
uintmax_t
ssize_t
ptrdiff_t
double
long double
signed char	*
short *
int *
long *
long long *
intmax_t *
size_t *
ptrdiff_t *
void *
*/
//my own integer len functions:
int		ft_charlen(char n, char base);
int		ft_shortlen(short n, short base);
int		ft_intlen(int n, int base);
int		ft_longlen(long n, long base);
int		ft_longlonglen(long long n, long long base);

int		ft_ucharlen(unsigned char n, unsigned char base);
int		ft_ushortlen(unsigned short n, unsigned short base);
int		ft_uintlen(unsigned int n, unsigned int base);
int		ft_ulonglen(unsigned long n, unsigned long base);
int		ft_ulonglonglen(unsigned long long n, unsigned long long base);


// EXTRA VA_LIST FUNCTIONS:
void	ft_varray(char **array, const char *format, ...);

#endif //PRINTF_H