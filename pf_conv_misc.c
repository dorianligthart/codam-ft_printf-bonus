#include "printf.h"

//adds desired to p->bytes.
//returns 0 <= i depending on how big size is.
int	ft_pfdesired(t_pfstruct *p, size_t desired)
{
	p->bytes += desired;
	if (p->bytes + FT_TERMINATOR < p->size)
		return (desired);
	else
		return ((p->size > (p->bytes - desired + FT_TERMINATOR)) \
				* (p->size - (p->bytes - desired + FT_TERMINATOR)));
}

//c: flags="-", fieldwidth, length-modifier.
//%: flags="-", fieldwidth.
void	ft_pf_c(t_pfstruct *p, t_pfconv *c)
{
	c->item.c = va_arg(p->ap, int);
	c->itemlen = 1;
	if (!c->minus && c->fw > c->itemlen)
		ft_memset(p->str + p->bytes - (c->fw - c->itemlen), ' ',
				  ft_pfdesired(p, c->fw - c->itemlen));
	if (ft_pfdesired(p, c->itemlen))
		p->str[p->bytes- c->itemlen] = c->item.c;
	if (c->minus && c->fw > c->itemlen)
		ft_memset(p->str + p->bytes - (c->fw - c->itemlen), ' ',
				  ft_pfdesired(p, c->fw - c->itemlen));
}

//s: flags="-", fieldwidth, precision, length-modifier.
void	ft_pf_s(t_pfstruct *p, t_pfconv *c)
{
	const char		*invalid = "(null)";
	const int		invlen = ft_strlen(invalid);
	size_t			strlen;

	c->item.s = va_arg(p->ap, char *);
	strlen = ft_strlen(c->item.s);
	c->itemlen = (c->item.s && strlen <= (size_t)c->prec) * strlen\
				+ (c->item.s && strlen > (size_t)c->prec) * c->prec\
				+ (!c->item.s && (!c->dot || c->prec >= invlen)) * invlen;
	if (c->item.s == NULL)
		c->item.s = (char *)invalid;
	if (!c->minus && c->fw > c->itemlen)
		ft_memset(p->str + p->bytes - (c->fw - c->itemlen), ' ',
				  ft_pfdesired(p, c->fw - c->itemlen));
	ft_memcpy(p->str + p->bytes - c->itemlen, c->item.s,
			  ft_pfdesired(p, c->itemlen));
	if (c->minus && c->fw > c->itemlen)
		ft_memset(p->str + p->bytes - (c->fw - c->itemlen), ' ',
				  ft_pfdesired(p, c->fw - c->itemlen));
}

//for p conversion :(
void	ft_pf_p(t_pfstruct *p, t_pfconv *c)
{
	const char		*invalid = "(nil)";
	const size_t	invlen = ft_strlen(invalid);
	size_t			sizelen;

	c->item.p = va_arg(p->ap, void *);
	sizelen = ft_sizelen((size_t)c->item.p, 16) + 2;
	c->itemlen = (c->item.p && sizelen > (size_t)c->prec) * sizelen\
				+ (c->item.p && sizelen <= (size_t)c->prec) * c->prec\
				+ (!c->item.p) * invlen;
	if (!c->minus && c->fw > c->itemlen)
		ft_memset(p->str + p->bytes - (c->fw - c->itemlen), ' ',
				  ft_pfdesired(p, c->fw - c->itemlen));
	if (c->item.p == NULL)
		ft_memcpy(p->str + p->bytes - invlen, invalid,
				  ft_pfdesired(p, invlen));
	else
	{
		c->hash = true;
		ft_pfsize(p, c, (size_t)c->item.p, "0123456789abcdef");
	}
	if (c->minus && c->fw > c->itemlen)
		ft_memset(p->str + p->bytes - (c->fw - c->itemlen), ' ',
				  ft_pfdesired(p, c->fw - c->itemlen));
}

//n: no flags.
void	ft_pf_n(t_pfstruct *p, t_pfconv *c)
{
	if (c->c == 'n' && c->lm == PF_LM_NONE)
		*c->item.n = p->bytes;
	else if (c->c == 'n' && c->lm == PF_LM_HH)
		*c->item.hhn = p->bytes;
	else if (c->c == 'n' && c->lm == PF_LM_H)
		*c->item.hn = p->bytes;
	else if (c->c == 'n' && c->lm == PF_LM_L)
		*c->item.ln = p->bytes;
	else if (c->c == 'n' && c->lm == PF_LM_LL)
		*c->item.lln = p->bytes;
	else if (c->c == 'n' && c->lm == PF_LM_J)
		*c->item.jn = p->bytes;
	else if (c->c == 'n' && c->lm == PF_LM_Z)
		*c->item.zn = p->bytes;
	else if (c->c == 'n' && c->lm == PF_LM_T)
		*c->item.tn = p->bytes;
}