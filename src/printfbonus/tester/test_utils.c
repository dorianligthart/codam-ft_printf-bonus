/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 02:07:41 by rjw           #+#    #+#                 */
/*   Updated: 2024/01/22 17:58:56 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/**
 * @brief The last argument must be 0 (zero) for termination.
*/
void	markup(char *str, ...)
{
	va_list	style;
	int		num_styles;
	int		minus_check;

	num_styles = 0;
	va_start(style, str);
	while (va_arg(style, int) != 0)
		num_styles++;
	va_end(style);
	va_start(style, str);
	if (num_styles == 0)
		printf("%s", str);
	else if (num_styles > 0)
	{
		minus_check = va_arg(style, int);
		printf("\033[%d", minus_check);
		while (--num_styles)
			printf(";%d", va_arg(style, int));
		printf("m%s\033[0m", str);
		fflush(stdout);
	}
	va_end(style);
}

size_t	strlen_esc(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] > 0 && s[i] <= 127)
		i++;
	return (i);
}
#define MARKUP "\033[1;32m"
#define MARKDOWN "\033[0m\n"

void	print_full_width(const int c)
{
	struct winsize	w;
	const int		markup = strlen_esc(MARKUP);
	const int		markdown = strlen_esc(MARKDOWN);
	char			*chr;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	chr = (char *)malloc((w.ws_col + markup + markdown + 1));
	memcpy(chr, MARKUP, markup);
	memset(chr + markup, c, w.ws_col);
	ft_strllcpy(chr + markup + w.ws_col, MARKDOWN, markdown + 1);
	printf("%s", chr);
	fflush(stdout);
	free(chr);
}

static char	*ft_str(int sign, int i, int n)
{
	char	*p;

	p = malloc((i + 1 + sign) * sizeof(char));
	if (!p)
		return (NULL);
	p[i + sign] = '\0';
	while (i-- > 0)
	{
		p[i + sign] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		p[0] = '-';
	return (p);
}

char	*tester_itoa(int n)
{
	int		sign;
	int		i;
	int		nn;

	if (n == -2147483648)
		return (strdup("-2147483648"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	i = 1;
	nn = n;
	while (nn >= 10 || (n == 0 && i == 0))
	{
		nn /= 10;
		i++;
	}
	return (ft_str(sign, i, n));
}

size_t	ft_strllcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
