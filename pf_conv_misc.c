#include "libft.h"

//adds desired to p->bytes.
//returns 0 <= i depending on how big size is.
int	ft_pfdesired(t_pfstruct *p, size_t desired)
{
	p->bytes += desired;
	if (p->size >= p->bytes + FT_TERMINATOR)
		return (desired);
	else
		return ((p->size > (p->bytes - desired + FT_TERMINATOR)) \
				* (p->size - (p->bytes - desired + FT_TERMINATOR)));
}

//c: flags="-", fieldwidth, length-modifier.
//%: flags="-", fieldwidth.
void	ft_vsnprintf_c(t_pfstruct *p, t_pfconv *c)
{
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

//warning: the second call of vsnprintf(), 
//  the char * or wchar_t * could potentially have changed.
//s: flags="-", fieldwidth, precision, length-modifier.
void	ft_vsnprintf_s(t_pfstruct *p, t_pfconv *c)
{
	const char	*invalid = "(null)";
	const int	invlen = ft_strlen(invalid);
	const int	strlen = ft_strlen(c->item.s);

	c->itemlen = (c->item.s && strlen >= c->prec) * strlen\
				+ (c->item.s && strlen < c->prec) * c->prec\
				+ (!c->item.s && (!c->dot || c->prec >= invlen)) * invlen;
	if (!c->item.s)
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

//n: no flags.
void	ft_vsnprintf_n(t_pfstruct *p, t_pfconv *c)
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