#include <stddef.h>

int ft_sizelen(size_t n, size_t base)
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
