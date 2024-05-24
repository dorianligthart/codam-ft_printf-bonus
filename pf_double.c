#include "printf.h"

void	ft_print_lf(t_pfstruct *p, t_pfconv *c)
{
	ft_memcpy(p->str + p->bytes - 30,
		"[%fFaAgGeE are unimplemented!]", ft_pfdesired(p, 30));
	c->item.lf = va_arg(p->ap, long double);
}

void	ft_print_f(t_pfstruct *p, t_pfconv *c)
{
	ft_memcpy(p->str + p->bytes - 30,
		"[%fFaAgGeE are unimplemented!]", ft_pfdesired(p, 30));
	c->item.f = va_arg(p->ap, double);
}
