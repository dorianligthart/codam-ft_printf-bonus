// This file serves as a test file to see certain printf behaviour.
// Also as a note file.
///////////////////////////////////////////////////////////

#include <stdio.h>

//	CONVERSIONS AND THEIR FLAGS:
//		c: flags="-",		fieldwidth.
//		s: flags="-",		fieldwidth, precision.
//		p: flags="-",		fieldwidth, precision==0.
//		di: flags="-+ 0",	fieldwidth, precision.
//		u: flags="-0",		fieldwidth, precision.
//		x: flags="-#0",		fieldwidth, precision.
//		X: flags="-#0",		fieldwidth, precision.
//		o: flags="-#0",		fieldwidth, precision.

//supposes: a = fieldwidth, b = arglen, c = precision.
int ft_printf_arg_len_cheat_sheet(int a, int b, int c)
{
	// // ERROR 3 values, if abc < 0 returns -1:
	// return ((a >= 0 && b >= 0 && c >= 0) * (a + b + c + 1) - 1)

	// // ERROR 2 values, if ab < 0 returns -1:
	// return ((a >= 0 && b >= 0) * (a + b + 1) - 1)

	// // c:
	// (void)b;
	// (void)c;
	// return ((a > 1) * a + 1);
	
	// s:
	// precision?	(c > -1 && c < b)
	// fieldwidth?	(a > (precision? || b)
	// arglen?		(b >= c)
	return (((a > (c > -1 && c < b) && a > b) * c) * a
			+ (c > -1 && c < b) * c);

	// p:
}

int main(void)
{
	// printf("'%10.1s'\n", "abc");
	printf("%d\n", ft_printf_arg_len_cheat_sheet(2, 4, 5));
	return 0;
}
