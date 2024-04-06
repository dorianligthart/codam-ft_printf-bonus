#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>
#include "libft.h"

#include <stdint.h>
#include <limits.h>

#if 1
#define PRINT_FLAGS
#endif

void cmp_int(const char *str, ...)
{
	static char	ftbuffer[1024];
	static char	buffer[1024];
	va_list		ap;

	va_start(ap, str);
	int own = 0;//ft_snprintf(ftbuffer, 1024, str, ap);
	int ret = vsnprintf(buffer, 1024, str, ap);
	write(1, RED, 7);
	printf("[%s]: ft_vsnprintf() returned: %d/%d and printed: \"%s\" vs the real: \"%s\"\n", str, own, ret, ftbuffer, buffer);
	write(1, RESET, 6);
	fflush(stdout);
	va_end(ap);
}

//c: flags="-", fieldwidth.
//s: flags="-", fieldwidth, precision.
//p: flags="-", fieldwidth, dot(?), !precision.
//di: flags="-+ 0", fieldwidth, precision.
//u: flags="-0", fieldwidth, precision.
//xXo: flags="-#0", fieldwidth, precision.
int main(void)
{
	cmp_int("%02d\n", 42);
	cmp_int("%0+2d\n", 42);
    return 0;
	cmp_int("%0 2d\n", 42);
	cmp_int("%02d\n", -42);
	cmp_int("%0+2d\n", -42);
	cmp_int("%0 2d\n", -42);
	cmp_int("%03d\n", 42);
	cmp_int("%0+3d\n", 42);
	cmp_int("%0 3d\n", 42);
	cmp_int("%03d\n", -42);
	cmp_int("%0+3d\n", -42);
	cmp_int("%0 3d\n", -42);
	cmp_int("%04d\n", 42);
	cmp_int("%0+4d\n", 42);
	cmp_int("%0 4d\n", 42);
	cmp_int("%04d\n", -42);
	cmp_int("%0+4d\n", -42);
	cmp_int("%0 4d\n", -42);
	cmp_int("%05d\n", 42);
	cmp_int("%0+5d\n", 42);
	cmp_int("%0 5d\n", 42);
	cmp_int("%05d\n", -42);
	cmp_int("%0+5d\n", -42);
	cmp_int("%0 5d\n", -42);
    
	cmp_int("%2d\n", 42);
	cmp_int("%+2d\n", 42);
	cmp_int("% 2d\n", 42);
	cmp_int("%2d\n", -42);
	cmp_int("%+2d\n", -42);
	cmp_int("% 2d\n", -42);
	cmp_int("%3d\n", 42);
	cmp_int("%+3d\n", 42);
	cmp_int("% 3d\n", 42);
	cmp_int("%3d\n", -42);
	cmp_int("%+3d\n", -42);
	cmp_int("% 3d\n", -42);
	cmp_int("%4d\n", 42);
	cmp_int("%+4d\n", 42);
	cmp_int("% 4d\n", 42);
	cmp_int("%4d\n", -42);
	cmp_int("%+4d\n", -42);
	cmp_int("% 4d\n", -42);
	cmp_int("%5d\n", 42);
	cmp_int("%+5d\n", 42);
	cmp_int("% 5d\n", 42);
	cmp_int("%5d\n", -42);
	cmp_int("%+5d\n", -42);
	cmp_int("% 5d\n", -42);

	printf("done!\n");
}
