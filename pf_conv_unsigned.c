#include "libft.h"
#include <stddef.h>

//provide: size_t *pow which is eq to 1 resulting:
//*pow = base^tothepowerof(sqrootof(n));
int ft_pfsizelen(size_t n, size_t base)
{
	int	len;

	len = 1;
	while (n >= base)
	{
		++len;
		n /= base;
	}
	return (len);
}

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
		p->str[p->bytes - desired + i] = basestr[n / extract];
		extract /= base;
		n /= base;
		i++;
	}
}

void ft_pfsize(t_pfstruct *p, t_pfconv *c, size_t n, const char *basestr)
{
	const char		*prfx = (char*)((c->c == 'b') * (size_t)"b" \
						+ (c->c == 'o') * (size_t)"0"           \
						+ (c->c == 'u') * (size_t)""            \
						+ (c->c == 'x') * (size_t)"0x"          \
						+ (c->c == 'X') * (size_t)"0X");
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

static inline bool	ft_pf_unsigned2(t_pfstruct *p, t_pfconv *c,
									const char *basestr, const int base)
{
	if (c->lm == PF_LM_L)
		return (c->item.lu = va_arg(p->ap, unsigned long),
				c->itemlen = ft_pfsizelen(c->item.lu, base),
				ft_pfsize(p, c, c->item.lu, basestr),
				true);
	else if (c->lm == PF_LM_LL)
		return (c->item.llu = va_arg(p->ap, unsigned long long),
				c->itemlen = ft_pfsizelen(c->item.llu, base),
				ft_pfsize(p, c, c->item.llu, basestr),
				true);
    else if (c->lm == PF_LM_J)
		return (c->item.ju = va_arg(p->ap, uintmax_t),
				c->itemlen = ft_pfsizelen(c->item.ju, base),
				ft_pfsize(p, c, c->item.ju, basestr),
				true);
    else if (c->lm == PF_LM_Z)
		return (c->item.zu = va_arg(p->ap, size_t),
				c->itemlen = ft_pfsizelen(c->item.zu, base),
				ft_pfsize(p, c, c->item.zu, basestr),
				true);
	else if (c->lm == PF_LM_T)
		return (c->item.tu = va_arg(p->ap, size_t),
				c->itemlen = ft_pfsizelen(c->item.tu, base),
				ft_pfsize(p, c, c->item.tu, basestr),
				true);
	return (false);
}

//returns (0);
//u: flags="-0", fieldwidth, precision.
//xXob: flags="-#0", fieldwidth, precision.
bool	ft_pf_unsigned(t_pfstruct *p, t_pfconv *c)
{
	const char	*basestr = (const char *)((c->c == 'b') * (size_t)"01"\
							+ (c->c == 'o') * (size_t)"01234567"\
							+ (c->c == 'u') * (size_t)"0123456789"\
							+ (c->c == 'x') * (size_t)"0123456789abcdef"\
							+ (c->c == 'X') * (size_t)"0123456789ABCDEF");
	const int	base = ft_strlen(basestr);

	if (c->lm == PF_LM_NONE)
		return (c->item.u = va_arg(p->ap, unsigned int),
				c->itemlen = ft_pfsizelen(c->item.u, base),
				ft_pfsize(p, c, c->item.u, basestr),
				true);
    else if (c->lm == PF_LM_HH)
		return (c->item.hhu = (unsigned char)va_arg(p->ap, unsigned int),
				c->itemlen = ft_pfsizelen(c->item.hhu, base),
				ft_pfsize(p, c, c->item.hhu, basestr),
				true);
    else if (c->lm == PF_LM_H)
		return (c->item.hu = (unsigned short)va_arg(p->ap, unsigned int),
				c->itemlen = ft_pfsizelen(c->item.hu, base),
				ft_pfsize(p, c, c->item.hu, basestr),
				true);
	return (ft_pf_unsigned2(p, c, basestr, base));
}
