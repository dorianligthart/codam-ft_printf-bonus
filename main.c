// make all && cc main.c
//Regular text
#define C_BLK "\e[0;30m"
#define C_RED "\e[0;31m"
#define C_GRN "\e[0;32m"
#define C_YEL "\e[0;33m"
#define C_BLU "\e[0;34m"
#define C_MAG "\e[0;35m"
#define C_CYN "\e[0;36m"
#define C_WHT "\e[0;37m"

//Regular bold text
#define C_BBLK "\e[1;30m"
#define C_BRED "\e[1;31m"
#define C_BGRN "\e[1;32m"
#define C_BYEL "\e[1;33m"
#define C_BBLU "\e[1;34m"
#define C_BMAG "\e[1;35m"
#define C_BCYN "\e[1;36m"
#define C_BWHT "\e[1;37m"

//Regular underline text
#define C_UBLK "\e[4;30m"
#define C_URED "\e[4;31m"
#define C_UGRN "\e[4;32m"
#define C_UYEL "\e[4;33m"
#define C_UBLU "\e[4;34m"
#define C_UMAG "\e[4;35m"
#define C_UCYN "\e[4;36m"
#define C_UWHT "\e[4;37m"

//Regular background
#define C_BLKB "\e[40m"
#define C_REDB "\e[41m"
#define C_GRNB "\e[42m"
#define C_YELB "\e[43m"
#define C_BLUB "\e[44m"
#define C_MAGB "\e[45m"
#define C_CYNB "\e[46m"
#define C_WHTB "\e[47m"

//High intensty background 
#define C_BLKHB "\e[0;100m"
#define C_REDHB "\e[0;101m"
#define C_GRNHB "\e[0;102m"
#define C_YELHB "\e[0;103m"
#define C_BLUHB "\e[0;104m"
#define C_MAGHB "\e[0;105m"
#define C_CYNHB "\e[0;106m"
#define C_WHTHB "\e[0;107m"

//High intensty text
#define C_HBLK "\e[0;90m"
#define C_HRED "\e[0;91m"
#define C_HGRN "\e[0;92m"
#define C_HYEL "\e[0;93m"
#define C_HBLU "\e[0;94m"
#define C_HMAG "\e[0;95m"
#define C_HCYN "\e[0;96m"
#define C_HWHT "\e[0;97m"

//Bold high intensity text
#define C_BHBLK "\e[1;90m"
#define C_BHRED "\e[1;91m"
#define C_BHGRN "\e[1;92m"
#define C_BHYEL "\e[1;93m"
#define C_BHBLU "\e[1;94m"
#define C_BHMAG "\e[1;95m"
#define C_BHCYN "\e[1;96m"
#define C_BHWHT "\e[1;97m"

//Reset
#define C_RESET "\e[0m"

#include "printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
// #include <limits.h>
#include <stdint.h> //SIZE_MAX

//size=SIZE_MAX means %n is being tested
void cmp(size_t size, const char *str, ...)
{
	fflush(stdout);
	static char	ftbuffer[1024];
	static char	buffer[1024];
	va_list 	ap1;
	va_list 	ap2;
	va_list 	ap3;

	va_start(ap1, str);
	va_copy(ap2, ap1);
	va_copy(ap3, ap1);
	int	capreal = vsnprintf(NULL, 0, str, ap1);
	if (capreal < 0)
		exit(1);
	size_t cap = (size < capreal) * size + (size >= capreal) * capreal;
	int own = ft_vsnprintf(ftbuffer, cap + 1, str, ap2);
	int ret = vsnprintf(buffer, cap + 1, str, ap3);
	if (own - ret != 0 || strncmp(ftbuffer, buffer, cap))
		write(1, C_RED, 7);
	else write(1, C_GRN, 7);
	printf("[%s]: ft_vsnprintf() returned: %d/%d and printed: \n\t \"%.*s\"\tvs the real:\n\t \"%.*s\"\n", str, own, ret, cap, ftbuffer, cap, buffer);
	write(1, C_RESET, 4);
	va_end(ap1);
	fflush(stdout);
	// if (own - ret != 0 || strncmp(ftbuffer, buffer, cap)) exit(1);
}

void	test_c(void);
void	test_s(void);
void	test_p(void);
void	test_di(void);
void	test_uxX(void);
void	test_n(void);

//COMPILE:
//make re && make test && ./a.out
//c: flags="-", fieldwidth.
//s: flags="-", fieldwidth, precision.
//p: flags="-", fieldwidth, dot(?), !precision.
//di: flags="-+ 0", fieldwidth, precision.
//u: flags="-0", fieldwidth, precision.
//xXo: flags="-#0", fieldwidth, precision.
int main(void)
{
	printf("valistsize=%zu\n", sizeof(va_list) * 3);
	// test_c(); //DONE!
	// test_s(); //DONE!
	// test_p();
	// test_di(); //DONE!
	// test_uxX(); //DONE!!
	// test_n(); 
    return 0;

	printf("done!\n");
}

//c: flags="-", fieldwidth.
void	test_c(void)
{
	// for (char x = 0; x < 127; ++x)
	// 	cmp(1, "%c", x);
	// cmp(1, "%c", 127);
	for (size_t x = 0; x < 4; ++x)
	{
		cmp(x, "%1c", 'a');
		cmp(x, "%2c", 'b');
		cmp(x, "%-1c", 'c');
		cmp(x, "%-2c", 'd');
	}
	cmp(69, "%*c", 1, 'y');
	cmp(69, "%*c", -1, 'Y');
	cmp(69, "%*2$c", 'z', 2, 3);
	cmp(69, "%*2$c", 'Z', -2, -3);
	cmp(69, "%*3$c", 'z', 2, 3);
	cmp(69, "%*3$c", 'Z', -2, -3);
	cmp(69, "%*3$c and %*1$c", 'z', 2, 3);
	cmp(69, "%*3$c and %*1$c", 'Z', -2, -3);
	cmp(69, "%*3$c and %*2$c", 'z', 2, 3);
	cmp(69, "%*3$c and %*2$c", 'Z', -2, -3);
	cmp(69, "%*3$c and %*3$c", 'z', 2, 3);
	cmp(69, "%*3$c and %*3$c", 'Z', -2, -3);
}

//s: flags="-", fieldwidth, precision.
void	test_s(void)
{
	const char	*str = "fortytwo";

	for (int x = 0; x <= ft_strlen(str); ++x)
	{
		cmp(42, "%.*s", x, str);
		cmp(42, "%1.*s", x, str);
		cmp(42, "%2.*s", x, str);
		cmp(42, "%3.*s", x, str);
		cmp(42, "%4.*s", x, str);
		cmp(42, "%5.*s", x, str);
		cmp(42, "%6.*s", x, str);
		cmp(42, "%7.*s", x, str);
		cmp(42, "%8.*s", x, str);
		cmp(42, "%9.*s", x, str);
	}
	for (int x = 0; x <= ft_strlen(str); ++x)
	{
		cmp(42, "%-.*s", x, str);
		cmp(42, "%-1.*s", x, str);
		cmp(42, "%-2.*s", x, str);
		cmp(42, "%-3.*s", x, str);
		cmp(42, "%-4.*s", x, str);
		cmp(42, "%-5.*s", x, str);
		cmp(42, "%-6.*s", x, str);
		cmp(42, "%-7.*s", x, str);
		cmp(42, "%-8.*s", x, str);
		cmp(42, "%-9.*s", x, str);
	}
	for (int x = 0; x <= 8; ++x)
		cmp(42, "%*.*s", x, x, NULL);
}

//p: flags="-", fieldwidth, dot(?), !precision.
void	test_p(void)
{
	cmp(42, "%p", 0x0);
	cmp(42, "%.0p", 0x0);
	// cmp(42, "%p", 0x1);
}

//di: flags="-+ 0", fieldwidth, precision.
void	test_di(void)
{
	for (size_t x = 1; x < 8; ++x) {
		cmp(x, "%02d", 42);
		cmp(x, "%0+2d", 42);
		cmp(x, "%0 2d", 42);
		cmp(x, "%02d", -42);
		cmp(x, "%0+2d", -42);
		cmp(x, "%0 2d", -42);
		cmp(x, "%03d", 42);
		cmp(x, "%0+3d", 42);
		cmp(x, "%0 3d", 42);
		cmp(x, "%03d", -42);
		cmp(x, "%0+3d", -42);
		cmp(x, "%0 3d", -42);
		cmp(x, "%04d", 42);
		cmp(x, "%0+4d", 42);
		cmp(x, "%0 4d", 42);
		cmp(x, "%04d", -42);
		cmp(x, "%0+4d", -42);
		cmp(x, "%0 4d", -42);
		cmp(x, "%05d", 42);
		cmp(x, "%0+5d", 42);
		cmp(x, "%0 5d", 42);
		cmp(x, "%05d", -42);
		cmp(x, "%0+5d", -42);
		cmp(x, "%0 5d", -42);
		cmp(x, "%2d", 42);
		cmp(x, "%+2d", 42);
		cmp(x, "% 2d", 42);
		cmp(x, "%2d", -42);
		cmp(x, "%+2d", -42);
		cmp(x, "% 2d", -42);
		cmp(x, "%3d", 42);
		cmp(x, "%+3d", 42);
		cmp(x, "% 3d", 42);
		cmp(x, "%3d", -42);
		cmp(x, "%+3d", -42);
		cmp(x, "% 3d", -42);
		cmp(x, "%4d", 42);
		cmp(x, "%+4d", 42);
		cmp(x, "% 4d", 42);
		cmp(x, "%4d", -42);
		cmp(x, "%+4d", -42);
		cmp(x, "% 4d", -42);
		cmp(x, "%5d", 42);
		cmp(x, "%+5d", 42);
		cmp(x, "% 5d", 42);
		cmp(x, "%5d", -42);
		cmp(x, "%+5d", -42);
		cmp(x, "% 5d", -42);
	}

	cmp(5, "%.d", 0);
	cmp(5, "%.0d", 0);
}

//u: flags="-0", fieldwidth, precision.
//xXo: flags="-#0", fieldwidth, precision.
void	test_uxX(void)
{
	cmp(5, "%.o", 0);
	cmp(5, "%.u", 0);
	cmp(5, "%.x", 0);
	for (size_t x = 1; x < 5; ++x) {
		cmp(x, "%02x", 42);
		cmp(x, "%02o", 42);
		cmp(x, "%0#2x", 42);
		cmp(x, "%0#2o", 42);
		cmp(x, "%0-2x", 42);
		cmp(x, "%0-2o", 42);
				cmp(x, "%0-2u", 42);
		cmp(x, "%03x", 42);
		cmp(x, "%03o", 42);
				cmp(x, "%03u", 42);
		cmp(x, "%0#3x", 42);
		cmp(x, "%0#3o", 42);
		cmp(x, "%0-3x", 42);
		cmp(x, "%0-3o", 42);
				cmp(x, "%0-3u", 42);
		cmp(x, "%04x", 42);
		cmp(x, "%04o", 42);
				cmp(x, "%04u", 42);
		cmp(x, "%0#4x", 42);
		cmp(x, "%0#4o", 42);
		cmp(x, "%0-4x", 42);
		cmp(x, "%0-4o", 42);
				cmp(x, "%0-4u", 42);
		cmp(x, "%2x", 42);
		cmp(x, "%2o", 42);
				cmp(x, "%2u", 42);
		cmp(x, "%#2x", 42);
		cmp(x, "%#2o", 42);
		cmp(x, "%-2x", 42);
		cmp(x, "%-2o", 42);
				cmp(x, "%-2u", 42);
		cmp(x, "%3x", 42);
		cmp(x, "%3o", 42);
				cmp(x, "%3u", 42);
		cmp(x, "%#3x", 42);
		cmp(x, "%#3o", 42);
		cmp(x, "%-3x", 42);
		cmp(x, "%-3o", 42);
				cmp(x, "%-3u", 42);
		cmp(x, "%4x", 42);
		cmp(x, "%4o", 42);
				cmp(x, "%4u", 42);
		cmp(x, "%#4x", 42);
		cmp(x, "%#4o", 42);
		cmp(x, "%-4x", 42);
		cmp(x, "%-4o", 42);
				cmp(x, "%-4u", 42);
	}
}

//n: no flags
void	test_n(void)
{
	const char	*str = "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789"\
					   "0123456789012345678901234567890123456789012345678901234567890123456789";
	int			n = 0;
	signed char	hhn = 0;
	short		hn = 0;
	long		ln = 0;
	long long	lln = 0;
	intmax_t	jn = 0;
	ssize_t		zn = 0;
	ptrdiff_t	tn = 0;
	int			ft_n = 0;
	signed char	ft_hhn = 0;
	short		ft_hn = 0;
	long		ft_ln = 0;
	long long	ft_lln = 0;
	intmax_t	ft_jn = 0;
	ssize_t		ft_zn = 0;
	ptrdiff_t	ft_tn = 0;
	
	ft_snprintf(NULL, 0, "%s%n", str, &ft_n);
	snprintf(NULL, 0, "%s%n", str, &n);
	if (ft_n != n) printf("ft_n doesn't eq n: %n != %n", ft_n, n);

	ft_snprintf(NULL, 0, "%s%hhn", str, &ft_hhn);
	snprintf(NULL, 0, "%s%hhn", str, &hhn);
	if (ft_hhn != hhn) printf("ft_hhn doesn't eq hhn: %hhn != %hhn", ft_hhn, hhn);

	ft_snprintf(NULL, 0, "%s%hn", str, &ft_hn);
	snprintf(NULL, 0, "%s%hn", str, &hn);
	if (ft_hn != hn) printf("ft_hn doesn't eq hn: %hn != %hn", ft_hn, hn);

	ft_snprintf(NULL, 0, "%s%ln", str, &ft_ln);
	snprintf(NULL, 0, "%s%ln", str, &ln);
	if (ft_ln != ln) printf("ft_ln doesn't eq ln: %ln != %ln", ft_ln, ln);

	ft_snprintf(NULL, 0, "%s%lln", str, &ft_lln);
	snprintf(NULL, 0, "%s%lln", str, &lln);
	if (ft_lln != lln) printf("ft_lln doesn't eq lln: %lln != %lln", ft_lln, lln);

	ft_snprintf(NULL, 0, "%s%jn", str, &ft_jn);
	snprintf(NULL, 0, "%s%jn", str, &jn);
	if (ft_jn != jn) printf("ft_jn doesn't eq jn: %jn != %jn", ft_jn, jn);

	ft_snprintf(NULL, 0, "%s%zn", str, &ft_zn);
	snprintf(NULL, 0, "%s%zn", str, &zn);
	if (ft_zn != zn) printf("ft_zn doesn't eq zn: %zn != %zn", ft_zn, zn);

	ft_snprintf(NULL, 0, "%s%tn", str, &ft_tn);
	snprintf(NULL, 0, "%s%tn", str, &tn);
	if (ft_tn != tn) printf("ft_tn doesn't eq tn: %tn != %tn", ft_tn, tn);

}
