#include <stddef.h>  //'size_t', NULL;
#include <stdlib.h>  //malloc(), free();
#include <unistd.h>  //write();
#include <stdarg.h>  //f(...), 'va_list', va_start(), va_arg(), va_end();
#include <stdbool.h> //'bool', true, false;
#include "libft.h"
#include <stdio.h>

static void	ft_vsnprintf_set_conv(t_pfstruct *p, t_pfconv *c)
{
	printf("\n\n[Conversion %%%c]:\n", *(p->format - 1));
	printf("\thash= %s\n", c->hash ? "true" : "false");
	printf("\tminus= %s\n", c->minus ? "true" : "false");
	printf("\tplus=  %s\n", c->plus ? "true" : "false");
	printf("\tspace= %s\n", c->space ? "true" : "false");
	printf("\tzero=  %s\n", c->zero ? "true" : "false");
	printf("\twidth= %d\n", c->width);
	printf("\tdot=   %s\n", c->dot ? "true" : "false");
	printf("\tprec=   %d\n", c->prec);
	printf("\tconv=  '%c'\n\n", c->c);
	if (ft_strchr("cs%", c->c))
		p->bytes += ft_printf_char(p, c);
	else if (ft_strchr("id", c->c))
		p->bytes += ft_printf_signed(p, c);
	else if (ft_strchr("ouxXpb", c->c))
		p->bytes += ft_printf_unsigned(p, c);
	else if (ft_strchr("fFeEaAgG", c->c))
		p->bytes += ft_printf_double(p, c);
	else if (c->c == 'n' && c->lm == 0)
		*c->item.n = p->bytes;
	else if (c->c == 'n' && c->lm == 1)
		*c->item.hhn = p->bytes;
	else if (c->c == 'n' && c->lm == 2)
		*c->item.hn = p->bytes;
	else if (c->c == 'n' && c->lm == 3)
		*c->item.ln = p->bytes;
	else if (c->c == 'n' && c->lm == 4)
		*c->item.lln = p->bytes;
	else if (c->c == 'n' && c->lm == 5)
		*c->item.jn = p->bytes;
	else if (c->c == 'n' && c->lm == 6)
		*c->item.zn = p->bytes;
	else if (c->c == 'n' && c->lm == 7)
		*c->item.tn = p->bytes;
}

static inline int ft_printf_get_lm(t_pfstruct *p)
{
	if (*p->format == 'h' && *(p->format + 1) == 'h' && ++(p->format) && ++(p->format))
		return (1);
	if (*p->format == 'h' && ++(p->format))
		return (2);
	if (*p->format == 'l' && *(p->format + 1) == 'l' && ++(p->format) && ++(p->format))
		return (4);
	if (*p->format == 'l' && ++(p->format))
		return (3);
	if (*p->format == 'j' && ++(p->format))
		return (5);
	if (*p->format == 'z' && ++(p->format))
		return (6);
	if (*p->format == 't' && ++(p->format))
		return (7);
	if (*p->format == 'L' && ++(p->format))
		return (8);
	return (0);
}

static inline void ft_printf_width_precision(t_pfstruct *p, int *wp)
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
	else if ((va && atoi)
			|| (va && atoi && *p->format == '$' && *p->format++))
	{
		va_copy(tmp, p->ap);
		while (atoi--)
			*wp = va_arg(tmp, int);
		va_end(tmp);
	}
}

// if (ft_strchr("cspdiuoxXfFeEaAgG%", **str))
void ft_vsnprintf_new_conv(t_pfstruct *p)
{
	static t_pfconv	conv;

	ft_memset(&conv, 0, sizeof(conv));
	while (ft_strchr("#-+ 0", *(++p->format)))
	{
		conv.hash = (conv.hash || *p->format == '#');
		conv.zero = (conv.zero || *p->format == '0');
		conv.minus = (conv.minus || *p->format == '-');
		conv.space = (conv.space || *p->format == ' ');
		conv.plus = (conv.plus || *p->format == '+');
	}
	if (*p->format >= '1' && *p->format <= '9')
		ft_printf_width_precision(p, &conv.width);
	conv.minus = (conv.minus || conv.width < 0);
	conv.width *= (conv.width < 0) * 2 - 1;
	if (*p->format == '.' && *p->format)
	{
		conv.dot = true;
		ft_printf_width_precision(p, &conv.prec);
	}
	conv.lm = ft_printf_get_lm(p);
	conv.c = *p->format++;
	ft_vsnprintf_set_conv(p, &conv);
}
