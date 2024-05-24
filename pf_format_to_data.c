#include "printf.h"
#include <stddef.h>  //'size_t', NULL;
#include <stdbool.h> //'bool', true, false;

static inline bool	choose_new_conversion(t_pfstruct *p, t_pfconv *c)
{
	void	(*funcptrs[128])(t_pfstruct *, t_pfconv *) = {['%'] = ft_print_c,
				['c'] = ft_print_c, ['s'] = ft_print_s, ['p'] = ft_print_p,
				['d'] = ft_print_i,	['i'] = ft_print_i, ['u'] = ft_print_u,
				['x'] = ft_print_u, ['X'] = ft_print_u, ['o'] = ft_print_u,
				['f'] = ft_print_f, ['F'] = ft_print_f, ['e'] = ft_print_f,
				['E'] = ft_print_f, ['a'] = ft_print_f, ['A'] = ft_print_f,
				['g'] = ft_print_f, ['G'] = ft_print_f, ['n'] = ft_print_n,};

	if (c->c == '%')
		c->item.c = '%';
	if ((ft_strchr("cs", c->c) && c->lm == PF_LM_L)
		|| !ft_strchr("%cspdiuxXbonfFeEaAgG", c->c))
		return (false);
	funcptrs[(int)c->c](p, c);
	return (true);
}

static inline int	get_lengthmodifier(t_pfstruct *p)
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

static inline void	get_fw_or_prec(t_pfstruct *p, int *wp)
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
		va_copy(tmp, p->oldap);
		while (atoi--)
			*wp = va_arg(tmp, int);
		va_end(tmp);
	}
}

bool	ft_print_new_conversion(t_pfstruct *p)
{
	static t_pfconv	conv;

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
		get_fw_or_prec(p, &conv.fw);
	if (conv.fw < 0)
	{
		conv.minus = true;
		conv.fw *= -1;
	}
	conv.dot = (*p->format == '.' && *p->format++);
	if (*(p->format - 1) == '.')
		get_fw_or_prec(p, &conv.prec);
	conv.lm = get_lengthmodifier(p);
	conv.c = *p->format++;
	return (choose_new_conversion(p, &conv));
}
