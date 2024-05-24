#ifndef PRINTF_H
# define PRINTF_H

# if defined(FT_TERMINATOR) || defined(FT_ERROR)
# else
#  define FT_TERMINATOR 1
#  define FT_ERROR -1
# endif

# include <stddef.h>  //various types
# include <stdbool.h> //'bool';
# include <wchar.h>   //'wint_t',  'wchar_t*' even though we don't support them;
# include <stdint.h>  //SIZE_MAX, 'intmax_t', 'uintmax_t'; 
# include <unistd.h>  //'ssize_t', 'size_t';
# include <stdarg.h>  //'va_list', '...', __attribute__

//activate printf functions and structs/union.
# ifndef VA_FORBIDDEN
//4bytes
//LF = long float
enum e_pflengthmod
{
	PF_LM_NONE = 0,
	PF_LM_HH,
	PF_LM_H,
	PF_LM_L,
	PF_LM_LL,
	PF_LM_J,
	PF_LM_Z,
	PF_LM_T,
	PF_LM_LF,
};

//note: wint_t and wchar_t * are unused in this project because wprintf(), wfprintf() and wsprintf() are unimplemented.
//8bytes
union u_pfunion
{
	char				c;
	wint_t				lc;
	char*				s;
	wchar_t*			ls;
	int					i;
	signed char			hhi;
	short				hi;
	long				li;
	long long			lli;
	intmax_t			ji;
	ssize_t				zi;
	ptrdiff_t			ti;
	unsigned int		u;
	unsigned char		hhu;
	unsigned short		hu;
	unsigned long		lu;
	unsigned long long	llu;
	uintmax_t			ju;
	size_t				zu;
	ptrdiff_t			tu;
	double				f;
	long double			lf;
	int					*n;
	signed char			*hhn;
	short				*hn;
	long				*ln;
	long long			*lln;
	intmax_t			*jn;
	ssize_t				*zn;
	ptrdiff_t			*tn;
	void				*p;
};

//last 3 values in this struct always needed. rest is optional.
//7 * sizeof(char) + 4 * sizeof(int) + sizeof(pf_union) = 31 -> 32bytes per conversion
typedef struct s_pfconv
{
	bool				hash;
	bool				minus;
	bool				plus;
	bool				space;
	bool				zero;
	int					fw;
	bool				dot;
	int					prec;
	int					lm;
	char				c;
	union u_pfunion		item;
	int					itemlen;
} t_pfconv;

//80 bytes
typedef struct s_pfstruct
{
	char    	*str;
	size_t  	size;
	const char	*format;
	va_list 	ap;
	va_list 	oldap;
	size_t     	bytes;
} t_pfstruct;

//Printf variants function definitions :

int ft_printf(const char *format, ...)\
	__attribute__((format (printf, 1, 2)));

int ft_sprintf(char *str, const char *format, ...)\
	__attribute__((format (printf, 2, 3)));

int ft_snprintf(char *str, size_t size, const char *format, ...)\
	__attribute__((format (printf, 3, 4)));

int ft_dprintf(int fd, const char *format, ...)\
	__attribute__((format (printf, 2, 3)));

int ft_dnprintf(int fd, size_t size, const char *format, ...)\
	__attribute__((format (printf, 3, 4)));

int ft_vprintf(const char *format, va_list ap);
int ft_vsprintf(char *str, const char *format, va_list ap);
int ft_vsnprintf(char *str, size_t size, const char *format, va_list ap);
int ft_vdprintf(int fd, const char *format, va_list ap);
int ft_vdnprintf(int fd, size_t size, const char *format, va_list ap);

//Conversion general functions :

		//(entry of new conversion)
bool	ft_print_new_conversion(t_pfstruct *p);

		//(checks if p->bytes + desired fit in p->size)
int		ft_pfdesired(t_pfstruct *p, size_t desired);

		//(puts unsigned digit on p->str)
void	ft_pfsize(t_pfstruct *p, t_pfconv *c, size_t n, const char *basestr);

//Conversion specific (one letter names) :

void	ft_print_c(t_pfstruct *p, t_pfconv *c);
void	ft_print_s(t_pfstruct *p, t_pfconv *c);
void	ft_print_p(t_pfstruct *p, t_pfconv *c);
void	ft_print_i(t_pfstruct *p, t_pfconv *c);
void	ft_print_u(t_pfstruct *p, t_pfconv *c);
void	ft_print_f(t_pfstruct *p, t_pfconv *c);
void	ft_print_n(t_pfstruct *p, t_pfconv *c);

# endif //#ifndef VA_FORBIDDEN

//NEW LIBFT :

int		ft_ssizelen(ssize_t n, ssize_t base);
int		ft_sizelen(size_t n, size_t base);

//OLD LIBFT :

void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *address, int c, size_t n);
size_t	ft_strlen(const char *str);

#endif //PRINTF_H
