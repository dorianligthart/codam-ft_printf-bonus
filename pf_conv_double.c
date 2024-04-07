#include "libft.h"

void	ft_pf_lf(t_pfstruct *p, t_pfconv *c)
{
	c->item.lf = va_arg(p->ap, double);
}

void	ft_pf_f(t_pfstruct *p, t_pfconv *c)
{
	c->item.f = va_arg(p->ap, double);
}

