/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:22:38 by doligtha          #+#    #+#             */
/*   Updated: 2024/02/05 03:15:07 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

#  ifndef ERROR_FTPRINTF
#   define ERROR_FTPRINTF -1
#  endif

#  ifndef UNREACHABLE_FTPRINTF
#   define UNREACHABLE_FTPRINTF 69
#  endif

#  ifndef UNIMPLEMENTED_FTPRINTF
#   define UNIMPLEMENTED_FTPRINTF 0
#  endif

#  include <stdbool.h>
#  include <stdarg.h>
#  include <stdint.h>
#  include <stddef.h>
#  include <unistd.h>

//ft_printf()'s union for all conversions. Note that:
//  wchar_t* and wint_t datatypes ARE NOT SUPPORTED (lengthmod "ls" and "lc"),
//	with the following statements in mind you can 
//  view this union as the actual printf() format string:
//    "i" could be "d",
//    "u" could be "x", "X", "o",
//    "f" could be "F", "e", "E", "a", "A", "g", "G",
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
	size_t				tu;

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

//conversion flags struct (in order of parsing). note that:
//  c = conversion character.
//  lengthmod value determined by ft_printf()'s format string:
//    0="",  1="hh", 2="h", 3="l", 4="ll",
//    5="j", 6="z",  7="t", 8="L".
//  arglen = the arglen acquired by the "./bon/len/*" functions.
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
	char	c;
	int		arglen;
}	t_pfconv;

typedef struct s_pflist
{
	union s_pfitem	item;
	t_pfconv		*conv;
	int				itemlen;
	struct s_pflist	*next;
}	t_pflist;


//length modifier functions :
//	signedinteger:
int	ft_signedchar_len(signed char n, signed char base);
int	ft_signedchar_paste(signed char n, signed char base, char *dst, t_pfconv *conv);
int	ft_short_len(short n, short base);
int	ft_short_paste(short n, short base, char *dst, t_pfconv *conv);
int	ft_int_len(int n, int base);
int	ft_int_paste(int n, int base, char *dst, t_pfconv *conv);
int	ft_long_len(long n, long base);
int	ft_long_paste(long n, long base, char *dst, t_pfconv *conv);
int	ft_longlong_len(long long n, long long base);
int	ft_longlong_paste(long long n, long long base, char *dst, t_pfconv *conv);
int	ft_ssize_t_len(ssize_t n, ssize_t base);
int	ft_ssize_t_paste(ssize_t n, ssize_t base, char *dst, t_pfconv *conv);
int	ft_intmax_len(intmax_t n, intmax_t base);
int	ft_intmax_paste(intmax_t n, intmax_t base, char *dst, t_pfconv *conv);
int	ft_ptrdiff_t_len(ptrdiff_t n, ptrdiff_t base);
int	ft_ptrdiff_t_paste(ptrdiff_t n, ptrdiff_t base, char *dst, t_pfconv *conv);
//	unsigned integer (note, 'uptrdiff_t' is obtained and parsed as 'size_t'):
int	ft_uchar_len(unsigned char n, unsigned char base);
int	ft_uchar_paste(unsigned char n, unsigned char base, char *dst, t_pfconv *conv);
int	ft_ushort_len(unsigned short n, unsigned short base);
int	ft_ushort_paste(unsigned short n, unsigned short base, char *dst, t_pfconv *conv);
int	ft_uint_len(unsigned int n, unsigned int base);
int	ft_uint_paste(unsigned int n, unsigned int base, char *dst, t_pfconv *conv);
int	ft_ulong_len(unsigned long n, unsigned long base);
int	ft_ulong_paste(unsigned long n, unsigned long base, char *dst, t_pfconv *conv);
int	ft_ulonglong_len(unsigned long long n, unsigned long long base);
int	ft_ulonglong_paste(unsigned long long n, unsigned long long base, char *dst, t_pfconv *conv);
int	ft_size_t_len(size_t n, size_t base);
int	ft_size_t_paste(size_t n, size_t base, char *dst, t_pfconv *conv);
int	ft_uintmax_len(uintmax_t n, uintmax_t base);
int	ft_uintmax_paste(uintmax_t n, uintmax_t base, char *dst, t_pfconv *conv);
//	(long) double:
int	ft_double_len(double d, char c, t_pfconv *conv, int prefixlen);
int	ft_double_paste(double d, char c, char *dst, t_pfconv *conv);
int	ft_longdouble_len(long double d, char c, t_pfconv *conv, int prefixlen);
int	ft_longdouble_paste(long double d, char c, char *dst, t_pfconv *conv);

//ft_printf()'s struct functions decl:
void	ft_pflistclear(t_pflist *pflist);
t_pflist	*ft_newpflist_append(t_pflist **pflist);
t_pfconv	*ft_newpfconv(void);

//ft_printf()'s main functions (read order down to up):
int	ft_pf_printpflist(int fd, t_pflist *origin, t_pflist *node, int total);
int	ft_pf_itemlen(union s_pfitem *item, t_pfconv *conv, char c);
void	ft_pf_set_va_arg(union s_pfitem *item, va_list *list, int lm, char c);
int	ft_printf(const char *format, ...) __attribute__((format (printf, 1, 2)));

// EXTRA VA_LIST FUNCTIONS:
void	ft_varray(char **array, const char *format, ...);

#endif //PRINTF_H