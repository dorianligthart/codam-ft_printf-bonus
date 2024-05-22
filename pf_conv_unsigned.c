#include "printf.h"
#include <stddef.h>
#include <stdbool.h>

	// printf("\n\n%zu, %zu, %zu, %u, \n", n, base, extract, desired);
static inline void	ft_pfsize2(t_pfstruct *p, t_pfconv *c, 
								size_t n, const char *basestr)
{
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
		p->str[p->bytes - c->itemlen + i] = basestr[n / extract];
		n %= extract;
		extract /= base;
		i++;
	}
}

void ft_pfsize(t_pfstruct *p, t_pfconv *c, size_t n, const char *basestr)
{
	const char		*prfx = (char*)((c->c == 'o') * (size_t)"0"
							+ (c->c == 'u') * (size_t)""
							+ (c->c == 'x') * (size_t)"0x"
							+ (c->c == 'X') * (size_t)"0X"
							+ (!ft_strchr("ouxX", c->c)) * (size_t)"");
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
		ft_pfsize2(p, c, n, basestr);
	if (c->minus && (size_t)c->fw > c->itemlen + prfxlen)
		ft_memset(p->str + p->bytes - (c->fw - prfxlen - c->prec - c->itemlen),
				  ' ', ft_pfdesired(p, c->fw - prfxlen - c->prec - c->itemlen));
}


//returns true if length modifier is valid, otherwise false.
static inline bool	ft_pf_u2(t_pfstruct *p, t_pfconv *c,
							 const char *basestr, const int base)
{
	if (c->lm == PF_LM_H)
		return (c->item.hu = (unsigned short)va_arg(p->ap, unsigned int),
				c->itemlen = ft_sizelen(c->item.hu, base),
				ft_pfsize(p, c, c->item.hu, basestr), true);
	else if (c->lm == PF_LM_L)
		return (c->item.lu = va_arg(p->ap, unsigned long),
				c->itemlen = ft_sizelen(c->item.lu, base),
				ft_pfsize(p, c, c->item.lu, basestr), true);
	else if (c->lm == PF_LM_LL)
		return (c->item.llu = va_arg(p->ap, unsigned long long),
				c->itemlen = ft_sizelen(c->item.llu, base),
				ft_pfsize(p, c, c->item.llu, basestr), true);
    else if (c->lm == PF_LM_J)
		return (c->item.ju = va_arg(p->ap, uintmax_t),
				c->itemlen = ft_sizelen(c->item.ju, base),
				ft_pfsize(p, c, c->item.ju, basestr), true);
    else if (c->lm == PF_LM_Z)
		return (c->item.zu = va_arg(p->ap, size_t),
				c->itemlen = ft_sizelen(c->item.zu, base),
				ft_pfsize(p, c, c->item.zu, basestr), true);
	else if (c->lm == PF_LM_T)
		return (c->item.tu = va_arg(p->ap, size_t),
				c->itemlen = ft_sizelen(c->item.tu, base),
				ft_pfsize(p, c, c->item.tu, basestr), true);
	return (false);
}

//returns (0);
//u: flags="-0", fieldwidth, precision.
//xXob: flags="-#0", fieldwidth, precision.
void	ft_pf_u(t_pfstruct *p, t_pfconv *c)
{
	const char	*basestr = (char *)((c->c == 'o') * (size_t)"01234567"
							+ (c->c == 'u') * (size_t)"0123456789"
							+ (c->c == 'x') * (size_t)"0123456789abcdef"
							+ (c->c == 'X') * (size_t)"0123456789ABCDEF");
	const int	base = ft_strlen(basestr);

	if (c->lm == PF_LM_NONE)
	{
		c->item.u = va_arg(p->ap, unsigned int);
		c->itemlen = ft_sizelen(c->item.u, base);
		ft_pfsize(p, c, c->item.u, basestr);
	}
    else if (c->lm == PF_LM_HH)
	{
		c->item.hhu = (unsigned char)va_arg(p->ap, unsigned int);
		c->itemlen = ft_sizelen(c->item.hhu, base);
		ft_pfsize(p, c, c->item.hhu, basestr);
	}
	else
		ft_pf_u2(p, c, basestr, base);
}
