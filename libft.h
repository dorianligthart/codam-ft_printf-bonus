#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>  //various types
# include <stdbool.h> //'bool';
# include <wchar.h>   //'wint_t',  'wchar_t*';
# include <stdint.h>  //SIZE_MAX, 'intmax_t', 'uintmax_t'; 
# include <unistd.h>  //'ssize_t', 'size_t';
# include <stdarg.h>  //'va_list', '...', __attribute__

# ifndef PF_ERROR
#  define PF_ERROR -1
# endif //PF_ERROR

# ifndef SSIZE_MAX
#  define SSIZE_MAX (SIZE_MAX / 2)
# endif //SSIZE_MAX

# ifndef SSIZE_MIN
#  define SSIZE_MIN ((SIZE_MAX / 2 + 1) * -1)
# endif //SSIZE_MIN

//8bytes
union u_pfunion
{
    int                 c;
    wint_t              lc;
    char*               s;
    wchar_t*            ls;
    int                 i;
    signed char         hhi;
    short               hi;
    long                li;
    long long           lli;
    intmax_t            ji;
    ssize_t             zi;
    ptrdiff_t           ti;
    unsigned int        u;
    unsigned char       hhu;
    unsigned short      hu;
    unsigned long       lu;
    unsigned long long  llu;
    uintmax_t           ju;
    size_t              zu;
    ptrdiff_t           tu;
    double              f;
    long double         Lf;
    int                 *n;
    signed char         *hhn;
    short               *hn;
    long                *ln;
    long long           *lln;
    intmax_t            *jn;
    ssize_t             *zn;
    ptrdiff_t           *tn;
    void                *p;
};

//last 3 values in this struct always needed. rest is optional.
//7 * sizeof(char) + 4 * sizeof(int) + sizeof(pf_union) = 31 -> 32bytes
typedef struct s_pfconv
{
    bool            hash;
    bool            minus;
    bool            plus;
    bool            space;
    bool            zero;
    int             width;
    bool            dot;
    int             prec;
    int             lm;
    char            c;
    union u_pfunion item;
    int             itemlen;
} t_pfconv;

//40 bytes
typedef struct s_pfstruct
{
    char    	*str;
    size_t  	size;
    const char	*format;
    va_list 	ap;
    size_t     	bytes;
} t_pfstruct;

//UTILS :
void	*ft_memcpy(void *dest, const void *src, size_t n);
char    *ft_strchr(const char *s, int c);
void    *ft_memset(void *address, int c, size_t n);
size_t  ft_strlen(const char *str);

void	ft_vsnprintf_new_conv(t_pfstruct *p);
int		ft_printf_char(t_pfstruct *p, t_pfconv *c);
int		ft_printf_signed(t_pfstruct *p, t_pfconv *c);
int		ft_intmax_len(ssize_t n, ssize_t base);
int		ft_printf_unsigned(t_pfstruct *p, t_pfconv *c);
int		ft_uintmax_len(size_t n, size_t base);
int		ft_printf_double(t_pfstruct *p, t_pfconv *c);

//PRINTF(like) FUNCTIONS :
int ft_printf(const char *format, ...)\
    __attribute__((format (printf, 1, 2)));
// int ft_fprintf(FILE *stream, const char *format, ...)\
//     __attribute__((format (fprintf, 1, 2, 3)));
int ft_sprintf(char *str, const char *format, ...)\
    __attribute__((format (printf, 2, 3)));
int ft_snprintf(char *str, size_t size, const char *format, ...)\
    __attribute__((format (printf, 3, 4)));
int ft_dprintf(int fd, const char *format, ...)\
    __attribute__((format (printf, 2, 3)));

//va_list instead of (...) printf-like:
int ft_vprintf(const char *format, va_list ap);
// int ft_vfprintf(FILE *stream, const char *format, va_list ap)
//     __attribute__((format (vfprintf, 1, 2, 3)));
int ft_vsprintf(char *str, const char *format, va_list ap);
int ft_vsnprintf(char *str, size_t size, const char *format, va_list ap);
int ft_vdprintf(int fd, const char *format, va_list ap);

#endif //LIBFT_H
