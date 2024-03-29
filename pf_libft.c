#include <stddef.h>  //'size_t', 'NULL';
#include <stdbool.h> //'bool', 'true', 'false';
#include <stdlib.h>  //malloc();
#include <unistd.h>  //write();
#include "libft.h"
#include <stdint.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n--)
		*(char *)(dest + n) = *(char *)(src + n);
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return ((char *)(s + i));
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

void	*ft_memset(void *address, int c, size_t n)
{
    while (n--)
        *((char *)address + n) = (char)c;
    return (address);
}

size_t	ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (*(str + i))
        i++;
    return (i);
}

