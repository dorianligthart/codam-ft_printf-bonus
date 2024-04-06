#include <stddef.h>  //'size_t', NULL;
#include <stdlib.h>  //malloc(), free();
#include <unistd.h>  //write();
#include <stdarg.h>  //f(...), 'va_list', va_start(), va_arg(), va_end();
#include <stdbool.h> //'bool', true, false;
#include "libft.h"
#include <stdio.h>

static inline bool	ft_pf_new_conversion2(t_pfstruct *p, t_pfconv *c)
{
	// printf("\n[Conversion %%%c]:\n", c->c);
	// printf("\thash=  %s\n", c->hash ? "true" : "false");
	// printf("\tminus= %s\n", c->minus ? "true" : "false");
	// printf("\tplus=  %s\n", c->plus ? "true" : "false");
	// printf("\tspace= %s\n", c->space ? "true" : "false");
	// printf("\tzero=  %s\n", c->zero ? "true" : "false");
	// printf("\tfw=    %d\n", c->fw);
	// printf("\tdot=   %s\n", c->dot ? "true" : "false");
	// printf("\tprec=  %d\n", c->prec);
	// printf("\tmod=   %d\n", c->lm);
	void (*funcptrs[128])(t_pfstruct *, t_pfconv *) = {['%'] = ft_pf_c,\
	['c'] = ft_pf_c, ['s'] = ft_pf_s, ['n'] = ft_pf_n};

	if (ft_strchr("cs", c->c) && c->lm == PF_LM_L)
		return (false);
	else if (c->c == '%')
		c->item.c = '%';
	else if (c->c == 'c')
		c->item.c = va_arg(p->ap, int);
	else if (c->c == 's')
		c->item.s = va_arg(p->ap, char *);
	else if (c->c == 'p')
		return (c->hash = true,
				c->item.p = va_arg(p->ap, void *),
				c->itemlen = ft_pfsizelen((size_t)c->item.p, 16),
				ft_pfsize(p, c, (size_t)c->item.p, "0123456789abcdef"),
				true);
	else if (ft_strchr("id", c->c))
		return (ft_pf_signed(p, c));
	else if (ft_strchr("bouxX", c->c))
		return (ft_pf_unsigned(p, c));
	else if (ft_strchr("fFeEaAgG", c->c))
		return (ft_pf_double(p, c), true);
	return (funcptrs[(int)c->c](p, c), true);
}

static inline int	ft_pf_get_lengthmodifier(t_pfstruct *p)
{
	if (*p->format == 'h' && *(p->format + 1) == 'h')
		return (p->format += 2, PF_LM_HH);
	if (*p->format == 'l' && *(p->format + 1) == 'l')
		return (p->format += 2, PF_LM_LL);
	if (*p->format == 'h')
		return (p->format += 1, PF_LM_H);
	if (*p->format == 'l')
		return (p->format += 1, PF_LM_L);
	if (*p->format == 'j')
		return (p->format += 1, PF_LM_J);
	if (*p->format == 'z')
		return (p->format += 1, PF_LM_Z);
	if (*p->format == 't')
		return (p->format += 1, PF_LM_T);
	if (*p->format == 'L')
		return (p->format += 1, PF_LM_LF);
	return (PF_LM_NONE);
}

static inline void	ft_pf_get_fw_or_prec(t_pfstruct *p, int *wp)
{
	int		atoi;
	bool	va;
	va_list tmp;

	va = (*p->format == '*' && *p->format++);
	atoi = 0;
	while (*p->format >= '0' && *p->format <= '9')
		atoi = atoi * 10 + *p->format++ - '0';
	if (!va)
		*wp = atoi;
	else if (va && !atoi)
		*wp = va_arg(p->ap, int);
	else if (va && atoi)
	{
		if (*p->format == '$')
			p->format++;
		va_copy(tmp, p->ap);
		while (atoi--)
			*wp = va_arg(tmp, int);
		va_end(tmp);
	}
}

// if (ft_strchr("cspdiuoxXfFeEaAgG%", **str))
bool	ft_pf_new_conversion(t_pfstruct *p)
{
	t_pfconv	conv;

	ft_memset(&conv, 0, sizeof(conv));
	while (ft_strchr("#-+ 0", *++p->format))
	{
		conv.hash = (conv.hash || *p->format == '#');
		conv.zero = (conv.zero || *p->format == '0');
		conv.minus = (conv.minus || *p->format == '-');
		conv.space = (conv.space || *p->format == ' ');
		conv.plus = (conv.plus || *p->format == '+');
	}
	if ((*p->format >= '1' && *p->format <= '9') || *p->format == '*')
		ft_pf_get_fw_or_prec(p, &conv.fw);
	if (conv.fw < 0)
	{
		conv.minus = true;
		conv.fw *= -1;
	}
	conv.dot = (*p->format == '.' && *p->format++);
	if (*(p->format - 1) == '.')
		ft_pf_get_fw_or_prec(p, &conv.prec);
	conv.lm = ft_pf_get_lengthmodifier(p);
	conv.c = *p->format++;
	return (ft_pf_new_conversion2(p, &conv));
}
