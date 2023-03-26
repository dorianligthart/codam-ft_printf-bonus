//TEST FILE FOR FT_PRINTF SUBJECT

#include "ft_printf.h"

void	leakchk(void)
{
	system("leaks -q a.out");
}

int main(int argc, char const *argv[])
{
	atexit(leakchk);

	ft_printf("0123456789\n");
	return 0;
}
