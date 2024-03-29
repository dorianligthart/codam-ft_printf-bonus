#include "libft.h"
#include <stddef.h>

int ft_uintmax_len(uintmax_t n, uintmax_t base)
{
	int	intlen;

	intlen = 1;
	while (n >= base)
	{
		n /= base;
		intlen++;
	}
	return (intlen);
}

static int pf_put_unsigned(t_pfstruct *p, t_pfconv *c,\
						   uintmax_t n, const char *basestr)
{
	return (0);
}

static inline int	ft_printf_signed2(t_pfstruct *p, t_pfconv *c,\
									  const char *basestr, const int base)
{
	if (c->lm == 4)
        return (c->item.llu = va_arg(p->ap, unsigned long long),\
				c->itemlen = ft_uintmax_len(c->item.llu, base),\
                pf_put_unsigned(p, c, c->item.lli, basestr));
    else if (c->lm == 5)
        return (c->item.ju = va_arg(p->ap, uintmax_t),\
				c->itemlen = ft_uintmax_len(c->item.ju, base),\
                pf_put_unsigned(p, c, c->item.ji, basestr));
    else if (c->lm == 6)
        return (c->item.zu = va_arg(p->ap, size_t),\
				c->itemlen = ft_uintmax_len(c->item.zu, base),\
                pf_put_unsigned(p, c, c->item.zi, basestr));
    else if (c->lm == 7)
		return (c->item.tu = va_arg(p->ap, size_t),\
				c->itemlen = ft_uintmax_len(c->item.tu, base),\
				pf_put_unsigned(p, c, c->item.ti, basestr));
	return (0);
}

//di: flags="-+ 0", fieldwidth, precision.
int	ft_printf_unsigned(t_pfstruct *p, t_pfconv *c)
{
    const char	*basestr = (const char *)((c->c == 'b') * (size_t)"01"\
							+ (c->c == 'o') * (size_t)"01234567"\
							+ (c->c == 'u') * (size_t)"0123456789"\
							+ (c->c == 'x') * (size_t)"0123456789abcdef"\
							+ (c->c == 'X') * (size_t)"0123456789ABCDEF");
	const int	base = ft_strlen(basestr);

	if (c->lm == 0)
        return (c->item.u = va_arg(p->ap, unsigned int),\
				c->itemlen = ft_uintmax_len(c->item.u, base),\
                pf_put_unsigned(p, c, c->item.i, basestr));
    else if (c->lm == 1)
        return (c->item.hhu = (unsigned char)va_arg(p->ap, unsigned int),\
				c->itemlen = ft_uintmax_len(c->item.hhu, base),\
                pf_put_unsigned(p, c, c->item.hhi, basestr));
    else if (c->lm == 2)
        return (c->item.hu = (unsigned short)va_arg(p->ap, unsigned int),\
				c->itemlen = ft_uintmax_len(c->item.hu, base),\
                pf_put_unsigned(p, c, c->item.hi, basestr));
	else if (c->lm == 3)
		return (c->item.lu = va_arg(p->ap, unsigned long),\
        		c->itemlen = ft_uintmax_len(c->item.lu, base),\
                pf_put_unsigned(p, c, c->item.li, basestr));
	return (ft_printf_signed2(p, c, basestr, base));
}
