#include <stddef.h>  //'size_t', 'NULL';
#include <stdbool.h> //'bool', 'true', 'false';
#include <stdlib.h>  //malloc();
#include <unistd.h>  //write();
#include "libft.h"
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>

int ft_ssize_len(ssize_t n, ssize_t base)
{
	int	intlen;

	intlen = 1;
	while (n <= -base || n >= base)
	{
		n /= base;
		intlen++;
	}
	return (intlen);
}

// static void pf_itoa2_helper(char *dest, ssize_t n, int len, char *basestr)
// {
//     int base;
// 
//     base = ft_strlen(basestr);
//     if (n == SSIZE_MIN)
//     {
//         dest[len-- - 1] = basestr[(n % base) * -1];
//         n /= base;
//     }
//     if (n < 0)
//         n = -n;
//     while (len--)
//     {
//         dest[len] = basestr[n % base];
//         n /= base;
//     }
// }

//CHANGE in values(compared to parent function):
//	adds sign to itemlen,
//	updates precision to actual zero's, 
//	updates fieldwidth to actual spaces/zeros,
//	negative boolean value to scaler for '0',
static int	pf_put_signed(t_pfstruct *p, t_pfconv *c,\
						  ssize_t n, int negative)
{
	char		result;
    const int	signlen = (negative || c->plus || c->space);

	(void)p;
	(void)n;
	c->itemlen += signlen;
    c->prec = (c->prec > c->itemlen + c->prec) * c->itemlen - c->prec;
    c->width -= (c->prec + c->itemlen);
    negative = negative * -2 + 1;
	result = 0;
	if (!c->minus && c->width)
	{
		
	}
	return (result);
}

static inline int	ft_printf_signed2(t_pfstruct *p, t_pfconv *c)
{
	if (c->lm == 4)
        return (c->item.lli = va_arg(p->ap, long long),\
				c->itemlen = ft_intmax_len(c->item.lli, 10),\
                pf_put_signed(p, c, c->item.lli, (c->item.lli < 0)));
    else if (c->lm == 5)
        return (c->item.ji = va_arg(p->ap, intmax_t),\
				c->itemlen = ft_intmax_len(c->item.ji, 10),\
                pf_put_signed(p, c, c->item.ji, (c->item.ji < 0)));
    else if (c->lm == 6)
        return (c->item.zi = va_arg(p->ap, ssize_t),\
				c->itemlen = ft_intmax_len(c->item.zi, 10),\
                pf_put_signed(p, c, c->item.zi, (c->item.zi < 0)));
    else if (c->lm == 7)
		return (c->item.ti = va_arg(p->ap, ptrdiff_t),\
				c->itemlen = ft_intmax_len(c->item.ti, 10),\
				pf_put_signed(p, c, c->item.ti, (c->item.ti < 0)));
	return (0);
}

//di: flags="-+ 0", fieldwidth, precision.
int	ft_printf_signed(t_pfstruct *p, t_pfconv *c)
{
    if (c->lm == 0)
        return (c->item.i = va_arg(p->ap, int),\
				c->itemlen = ft_intmax_len(c->item.i, 10),\
                pf_put_signed(p, c, c->item.i, (c->item.i < 0)));
    else if (c->lm == 1)
        return (c->item.hhi = (signed char)va_arg(p->ap, int),\
				c->itemlen = ft_intmax_len(c->item.hhi, 10),\
                pf_put_signed(p, c, c->item.hhi, (c->item.hhi < 0)));
    else if (c->lm == 2)
        return (c->item.hi = (short)va_arg(p->ap, int),\
				c->itemlen = ft_intmax_len(c->item.hi, 10),\
                pf_put_signed(p, c, c->item.hi, (c->item.hi < 0)));
	else if (c->lm == 3)
		return (c->item.li = va_arg(p->ap, long),\
        		c->itemlen = ft_intmax_len(c->item.li, 10),\
                pf_put_signed(p, c, c->item.li, (c->item.li < 0)));
	return (ft_printf_signed2(p, c));
}

