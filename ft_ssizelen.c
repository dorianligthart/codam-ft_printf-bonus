#include <unistd.h>

int ft_ssizelen(ssize_t n, ssize_t base)
{
	int	len;

	len = 1;
	while (n <= -base || n >= base)
	{
		++len;
		n /= base;
	}
	return (len);
}
