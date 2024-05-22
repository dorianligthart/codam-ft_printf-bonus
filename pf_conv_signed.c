#include "printf.h"
#include <unistd.h>  //'size_t', 'NULL';
#include <stdbool.h> //'bool', 'true', 'false';

	// printf("\n\n%zi, %zi, %zi, %zi, %i, \n", n, abs, base, extract, desired);
static inline void	ft_pfssize2(t_pfstruct *p, t_pfconv *c, 
								ssize_t n, const char *basestr)
{
	const ssize_t	abs = (n >= 0) * 2 - 1;
	const ssize_t	base = ft_strlen(basestr);
	ssize_t			extract;
	int				desired;
	int				i;

	extract = 1;
	while (extract <= n / base * abs)
		extract *= base;
	desired = ft_pfdesired(p, c->itemlen);
	i = 0;
	while (i < desired)
	{
		p->str[p->bytes - c->itemlen + i] = basestr[(n / extract) * abs];
		n %= extract;
		extract /= base;
		i++;
	}
}

//CHANGE in values(compared to parent function):
//	adds sign to itemlen,
//	updates precision to actual zero's, 
//	updates fieldwidth to actual spaces/zeros,
//	negative boolean value to scaler for '0',
void	ft_pfssize(t_pfstruct *p, t_pfconv *c, ssize_t n, const char *basestr)
{
	const char		*prfx = (char*)(
							  (n >= 0 && c->plus && !c->space) * (size_t)"+"
							+ (n >= 0 && !c->plus && c->space) * (size_t)" "
							+ (n >= 0 && !c->plus && !c->space) * (size_t)""
							+ (n < 0) * (size_t)"-");
	const int		prfxlen = ft_strlen(prfx);

	if (c->prec > c->itemlen)
		c->prec -= c->itemlen;
	if (!c->dot && c->zero && c->fw > c->itemlen + prfxlen)
		c->prec = c->fw - c->itemlen - prfxlen;
	if (!c->minus && !c->zero && c->fw > c->itemlen + prfxlen)
		ft_memset(p->str + p->bytes - (c->fw - prfxlen - c->prec - c->itemlen),
				  ' ', ft_pfdesired(p, c->fw - prfxlen - c->prec - c->itemlen));
	if (prfxlen && !(n == 0 && c->dot && !c->prec))
		ft_memcpy(p->str + p->bytes - (prfxlen),
				  prfx, ft_pfdesired(p, prfxlen));
	if (c->prec)
		ft_memset(p->str + p->bytes - (c->prec),
				  '0', ft_pfdesired(p, c->prec));
	if (!(n == 0 && c->dot && !c->prec))
		ft_pfssize2(p, c, n, basestr);
	if (c->minus && c->fw > c->itemlen + prfxlen)
		ft_memset(p->str + p->bytes - (c->fw - prfxlen - c->prec - c->itemlen),
				  ' ', ft_pfdesired(p, c->fw - prfxlen - c->prec - c->itemlen));
}

//returns true if length modifier is valid, otherwise false.
static inline bool	ft_pf_i2(t_pfstruct *p, t_pfconv *c, const char *basestr)
{
	if (c->lm == PF_LM_L)
		return (c->item.li = va_arg(p->ap, long),
				c->itemlen = ft_ssizelen(c->item.li, 10),
				ft_pfssize(p, c, c->item.li, basestr), true);
	else if (c->lm == PF_LM_LL)
		return (c->item.lli = va_arg(p->ap, long long),
				c->itemlen = ft_ssizelen(c->item.lli, 10),
				ft_pfssize(p, c, c->item.lli, basestr), true);
	else if (c->lm == PF_LM_J)
		return (c->item.ji = va_arg(p->ap, intmax_t),
				c->itemlen = ft_ssizelen(c->item.ji, 10),
				ft_pfssize(p, c, c->item.ji, basestr), true);
	else if (c->lm == PF_LM_Z)
		return (c->item.zi = va_arg(p->ap, ssize_t),
				c->itemlen = ft_ssizelen(c->item.zi, 10),
				ft_pfssize(p, c, c->item.zi, basestr), true);
	else if (c->lm == PF_LM_Z)
		return (c->item.ti = va_arg(p->ap, ptrdiff_t),
				c->itemlen = ft_ssizelen(c->item.ti, 10),
				ft_pfssize(p, c, c->item.ti, basestr), true);
	return (false);
}

//di: flags="-+ 0", fieldwidth, precision.
void	ft_pf_i(t_pfstruct *p, t_pfconv *c)
{
	const char	*basestr = "0123456789";

	if (c->lm == PF_LM_NONE)
	{
		c->item.i = va_arg(p->ap, int);
		c->itemlen = ft_ssizelen(c->item.i, 10);
		ft_pfssize(p, c, c->item.i, basestr);
	}
	else if (c->lm == PF_LM_HH)
	{
		c->item.hhi = (signed char)va_arg(p->ap, int);
		c->itemlen = ft_ssizelen(c->item.hhi, 10);
		ft_pfssize(p, c, c->item.hhi, basestr);
	}
	else if (c->lm == PF_LM_H)
	{
		c->item.hi = (short)va_arg(p->ap, int);
		c->itemlen = ft_ssizelen(c->item.hi, 10);
		ft_pfssize(p, c, c->item.hi, basestr);
	}
	else
		ft_pf_i2(p, c, basestr);
}
