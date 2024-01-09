// This file serves as a test file to see certain printf behaviour.
// Also as a note file.
///////////////////////////////////////////////////////////

#include <stdio.h>

// // maybe union instead of 'void *item'?????????
// union item
// {
// 	char c;
// 	char *s;
// 	unsigned long p;
// 	int d;
// 	int i;
// 	unsigned int u;
// 	unsigned int x;
// 	unsigned int X;
// 	unsigned int o;
// 	unsigned int %;
// }; //8 bytes

//	CONVERSIONS AND THEIR FLAGS:
//		c: flags="-",		fieldwidth.
//		s: flags="-",		fieldwidth, precision.
//		p: flags="-",		fieldwidth, precision does nothing unless = 0.
//		di: flags="-+ 0",	fieldwidth, precision.
//		u: flags="-0",		fieldwidth, precision.
//		x: flags="-#0",		fieldwidth, precision.
//		X: flags="-#0",		fieldwidth, precision.
//		o: flags="-#0",		fieldwidth, precision.

//supposes: a = fieldwidth, b = len of arg, c = precision.
int ft_printf_arg_len_cheat_sheet(int a, int b, int c)
{
	int	width = a;
	int	length = b;
	int	precision = c;
	// // ERROR 3 values, if abc < 0 returns -1:
	// return ((a >= 0 && b >= 0 && c >= 0) * (a + b + c + 1) - 1)

	// // ERROR 2 values, if ab < 0 returns -1:
	// return ((a >= 0 && b >= 0) * (a + b + 1) - 1)

	// // c:
	// (void)b;
	// (void)c;
	// return (((a > 1) * a - 1) + 1);
	
	// // s:
	// 	// fieldwidth?	((a > precision?) || a > b) * a
	// 	// arglen?		(b >= c)
	// 	// precision?	(c > -1 && c < b) * c
	// 	// (a > b || a > c) * a
	// return (((c > -1 && c < b && a > c) || !(c > -1 && c < b && a > b)) * a
	// 		+ !(c > -1 && c < b && c > a && b > a) * b
	// 		+ (c > -1 && c < b && c > a) * c);

	// p:
}

int main(void)
{
	char *p = 0;
	// *p = 0;

	printf("%.4p\n", p);
	// printf("'%10.1s'\n", "abc");
	// printf("%d\n", ft_printf_arg_len_cheat_sheet(2, 4, 5));
	return 0;
}
