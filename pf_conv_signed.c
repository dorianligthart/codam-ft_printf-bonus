#include <stddef.h>  //'size_t', 'NULL';
#include <stdbool.h> //'bool', 'true', 'false';
#include <stdlib.h>  //malloc();
#include <unistd.h>  //write();
#include "libft.h"
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>

//provide: ssize_t *pow which is eq to 1 resulting:
//*pow = base^tothepowerof(sqrootof(n));
int ft_pfssizelen(ssize_t n, ssize_t base)
{
	int	len;

	len = 1;
	while (n <= -base || n >= base)
	{
		++len;
		n /= base;
	}
	return (len);
}

static inline void	ft_pfssize2(t_pfstruct *p, t_pfconv *c, 
								ssize_t n, const char *basestr)
{
	const int		abs = (n >= 0) * 2 - 1;
	const size_t	base = ft_strlen(basestr);
	size_t			extract;
	int				desired;
	int				i;

	extract = 1;
	while (extract <= n / base)
		extract *= base;
	desired = ft_pfdesired(p, c->itemlen);
	i = 0;
	while (i < desired)
	{
		p->str[p->bytes - desired + i] = basestr[n / extract * abs];
		extract /= base;
		n /= base;
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
	const char		*prfx = (char*)( \
							  (n >= 0 && c->plus && !c->space) * (size_t)"+" \
							+ (n >= 0 && !c->plus && c->space) * (size_t)" " \
							+ (n >= 0 && !c->plus && !c->space) * (size_t)"" \
							+ (n < 0) * (size_t)"-");
	const size_t	prfxlen = ft_strlen(prfx);
	
	if (c->prec > c->itemlen)
		c->prec -= c->itemlen;
	if (!c->dot && c->zero && (size_t)c->fw > c->itemlen + prfxlen)
		c->prec = c->fw - c->itemlen - prfxlen;
	if (!c->minus && !c->zero && (size_t)c->fw > c->itemlen + prfxlen)
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
	if (c->minus && (size_t)c->fw > c->itemlen + prfxlen)
		ft_memset(p->str + p->bytes - (c->fw - prfxlen - c->prec - c->itemlen),
				  ' ', ft_pfdesired(p, c->fw - prfxlen - c->prec - c->itemlen));
}

static inline bool	ft_pfsigned2(t_pfstruct *p, t_pfconv *c, const char *basestr)
{
	if (c->lm == PF_LM_LL)
		return (c->item.lli = va_arg(p->ap, long long),
				c->itemlen = ft_pfssizelen(c->item.lli, 10),
				ft_pfssize(p, c, c->item.lli, basestr), true);
	else if (c->lm == PF_LM_J)
		return (c->item.ji = va_arg(p->ap, intmax_t),
				c->itemlen = ft_pfssizelen(c->item.ji, 10),
				ft_pfssize(p, c, c->item.ji, basestr), true);
	else if (c->lm == PF_LM_Z)
		return (c->item.zi = va_arg(p->ap, ssize_t),
				c->itemlen = ft_pfssizelen(c->item.zi, 10),
				ft_pfssize(p, c, c->item.zi, basestr), true);
	return (c->item.ti = va_arg(p->ap, ptrdiff_t),
			c->itemlen = ft_pfssizelen(c->item.ti, 10),
			ft_pfssize(p, c, c->item.ti, basestr), true);
	return (false);
}

//returns (0);
//di: flags="-+ 0", fieldwidth, precision.
bool	ft_pfsigned(t_pfstruct *p, t_pfconv *c)
{
	const char	*basestr = "0123456789";

	if (c->lm == PF_LM_NONE)
		return (c->item.i = va_arg(p->ap, int),
				c->itemlen = ft_pfssizelen(c->item.i, 10),
				ft_pfssize(p, c, c->item.i, basestr), true);
	else if (c->lm == PF_LM_HH)
		return (c->item.hhi = (signed char)va_arg(p->ap, int),
				c->itemlen = ft_pfssizelen(c->item.hhi, 10),
				ft_pfssize(p, c, c->item.hhi, basestr), true);
	else if (c->lm == PF_LM_H)
		return (c->item.hi = (short)va_arg(p->ap, int),
				c->itemlen = ft_pfssizelen(c->item.hi, 10),
				ft_pfssize(p, c, c->item.hi, basestr), true);
	else if (c->lm == PF_LM_L)
		return (c->item.li = va_arg(p->ap, long),
				c->itemlen = ft_pfssizelen(c->item.li, 10),
				ft_pfssize(p, c, c->item.li, basestr), true);
	return (ft_pfsigned2(p, c, basestr));
}

