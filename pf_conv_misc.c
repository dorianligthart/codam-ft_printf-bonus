#include "printf.h"
#include <stddef.h>
#include <stdbool.h>

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

//reason we don't need to cast 'fw' to size_t is that it's always unsigned
//s: flags="-", fieldwidth, precision, length-modifier.
void	ft_pf_s(t_pfstruct *p, t_pfconv *c)
{
	const char		*invalid = "(null)";
	const size_t	len = ft_strlen(invalid);
	size_t			strlen;
	const size_t	field = (size_t)c->fw;

	c->item.s = va_arg(p->ap, char *);
	if (c->item.s == NULL)
		c->item.s = (char *)invalid;
	strlen = ft_strlen(c->item.s);
	if (c->dot && (size_t)c->prec < strlen)
		strlen = (size_t)c->prec;
	if (c->item.s == invalid)
		strlen *= (!c->dot || (size_t)c->prec >= len);
	if (!c->minus && field > strlen)
		ft_memset(p->str + p->bytes - (field - strlen), ' ',
				  ft_pfdesired(p, field - strlen));
	ft_memcpy(p->str + p->bytes - strlen, c->item.s,
			  ft_pfdesired(p, strlen));
	if (c->minus && field > strlen)
		ft_memset(p->str + p->bytes - (field - strlen), ' ',
				  ft_pfdesired(p, field - strlen));
}

//for p conversion :(
void	ft_pf_p(t_pfstruct *p, t_pfconv *c)
{
	const char		*invalid = "(nil)";
	const size_t	len = ft_strlen(invalid);
	size_t			sizelen;

	c->hash = true;
	c->item.p = va_arg(p->ap, void *);
	sizelen = ft_sizelen((size_t)c->item.p, 16) + 2;
	c->itemlen = (c->item.p && (int)sizelen > c->prec) * sizelen\
				+ (c->item.p && (int)sizelen <= c->prec) * c->prec\
				+ (!c->item.p) * len;
	if (!c->minus && c->fw > c->itemlen)
		ft_memset(p->str + p->bytes - (c->fw - c->itemlen), ' ',
				  ft_pfdesired(p, c->fw - c->itemlen));
	if (c->item.p == NULL)
		ft_memcpy(p->str + p->bytes - len, invalid,
				  ft_pfdesired(p, len));
	else
		ft_pfsize(p, c, (size_t)c->item.p, "0123456789abcdef");
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
