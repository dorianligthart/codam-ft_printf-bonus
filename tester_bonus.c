/*
make and debug :
make bonus && cc -Iinclude -Wall -Werror -Wextra -fsanitize=address tester_bonus.c libftprintf.a && ./a.out
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

// #include "libft.h"
#include "printf.h"
#include <string.h>
#include <unistd.h>

#  define RESET "\033[0m"
#  define BLACK "\033[0;30m"
#  define RED "\033[0;31m"
#  define GREEN "\033[0;32m"
#  define YELLOW "\033[0;33m"
#  define BLUE "\033[0;34m"
#  define MAGENTA "\033[0;35m"
#  define CYAN "\033[0;36m"
#  define WHITE "\033[0;37m"

// https://patorjk.com/software/taag/
#define PRINTF_ASCII_ART \
"########################################################################################"\
"\n#           /      _  _ ___             _       _    __   _            _               #"\
"\n#           /     | || |__ \\           (_)     | |  / _| | |          | |              #"\
"\n#   _,,   (/ ~    | || |_ ) |_ __  _ __ _ _ __ | |_| |_  | |_ ___  ___| |_ ___ _ __    #"\
"\n#  \"-=\\;  '| [}   |__   _/ /| '_ \\| '__| | '_ \\| __|  _| | __/ _ \\/ __| __/ _ \\ '__|   #"\
"\n#   _ \\\\; __X%%       | |/ /_| |_) | |  | | | | | |_| |   | ||  __/\\__ \\ ||  __/ |      #"\
"\n#   _\\| \\__%%%%        |_|____| .__/|_|  |_|_| |_|\\__|_|    \\__\\___||___/\\__\\___|_|      #"\
"\n#   \\  \\/\\                  | |                                                        #"\
"\n#       ( )~~~              |_|     BONUS :)                                           #"\
"\n#       | \\                                     github.com/dorianligthart              #"\
"\n#     /  /                      \\(^-^)/                                                #"\
"\n########################################################################################"


static int	ft_putint(int nbr)
{
	char	basestr[] = "0123456789";
	int		divider;
	char	put[21];
	int		y;

	if (nbr == INT_MIN)
		return(write(1, "-2147483648", 11));
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
	}
	divider = 1;
	while (divider <= nbr / 10)
		divider = divider * 10;
	y = 0;
	while (divider)
	{
		put[y] = basestr[nbr / divider];
		nbr = nbr % divider;
		divider = divider / 10;
		y++;
	}
	put[y] = '\0';
	return (write(1, put, y));
}

// static void	print_va_list(const char *form, va_list list)
// {
// 	write(1, "\'"YELLOW, 9);
// 	if (form)
// 		write(1, form, strlen(form));
// 	write(1, RESET"\':", 6);
		
// 		write(1, "\nprintf:    \'", 13);
// 		int x = printf(form, va_arg(list, void *));
// 		fflush(stdout);
// 		write(1, "\'-->", 4);
// 		ft_putint(x);
		
// 		write(1, "\nft_printf: \'", 13);
// 		int y = ft_printf(form, va_arg(list, void *));
// 		fflush(stdout);
// 		write(1, "\'-->", 4);
// 		ft_putint(y);

// 		if (x != y)
// 			write(1, RED"\t\tdifference!"RESET"\n\n", 26);
// 		else
// 			write(1, "\t\t"GREEN"OK."RESET"\n\n", 17);
// }

static void	print1argdiff(const char *form, void *arg)
{
	write(1, "\'"YELLOW, 9);
	if (form)
		write(1, form, strlen(form));
	write(1, RESET"\':", 6);
		write(1, "\nprintf:    \'", 13);
		int x = printf(form, arg);
		fflush(stdout);
		write(1, "\'--> ", 5);
		ft_putint(x);
		
		write(1, "\nft_printf: \'", 13);
		int y = ft_printf(form, arg);
		fflush(stdout);
		write(1, "\'--> ", 5);
		ft_putint(y);

		if (x != y)
			write(1, RED"\t\tdifference!"RESET"\n", 26);
		else
			write(1, "\t\t"GREEN"OK."RESET"\n", 17);
}

void diffintegers(const char *form, void *arg)
{
	(void)form;
	(void)arg;
	return ;
}

//TESTER:
int	main(void)
{
printf(CYAN PRINTF_ASCII_ART RESET"\n");
write(1, "\n"BLUE"[format string test]"RESET"\n", 34);
//UB segfault check:
	print1argdiff("%zbcd", NULL);
	print1argdiff("%", NULL);
	print1argdiff("abcd%", NULL);
	print1argdiff("%%%", NULL);
	print1argdiff("abcd%%%", NULL);
	print1argdiff("%%%abcd", NULL);
//no UB check:
	// print1argdiff(NULL, NULL);
	print1argdiff("", NULL);
	print1argdiff("\0", NULL);
	print1argdiff("6", NULL);
	print1argdiff("abcd", NULL);
	print1argdiff("%%", NULL);
	print1argdiff("%%abcd", NULL);
	print1argdiff("abcd%%", NULL);
	return 0;
	
//c: flags="-", fieldwidth.
write(1, "\n"BLUE"[c conversion]"RESET"\n", 28);
	int	i = -1;
	while (++i < 128)
		print1argdiff("%c", (void *)(long)i);

//s: flags="-", fieldwidth, precision.
write(1, "\n"BLUE"[s conversion]"RESET"\n", 28);
	print1argdiff("%s", (void *)"");
	print1argdiff("%s", (void *)"\0");
	print1argdiff("%s", (void *)NULL);
	print1argdiff("%s", (void *)"6");
	print1argdiff("%s", (void *)"abcd");

//p: flags="-", fieldwidth, precision==0.
write(1, "\n"BLUE"[p conversion]"RESET"\n", 28);
	i = -1;
	while (++i < 3)
		diffintegers("%p", (void *)(ULONG_MAX - 1 + i));

//di: flags="-+ 0", fieldwidth, precision.
write(1, "\n"BLUE"[di conversion]"RESET"\n", 29);
	diffintegers("%i", (void *)-1);
	diffintegers("%i", (void *)0);
	diffintegers("%i", (void *)1);
	diffintegers("%i", (void *)10);
	i = -1;
	while (++i < 3)
		diffintegers("%i", (void *)(INT_MAX - 1 + (long)i));

//u: flags="-0", fieldwidth, precision.
write(1, "\n"BLUE"[u conversion]"RESET"\n", 28);
	i = -1;
	while (++i < 3)
		diffintegers("%u", (void *)(UINT_MAX - 1 + (long)i));

//x: flags="-#0", fieldwidth, precision.
write(1, "\n"BLUE"[x conversion]"RESET"\n", 28);
	i = -1;
	while (++i < 3)
		diffintegers("%x", (void *)(ULONG_MAX - 1 + i));
	
//X: flags="-#0", fieldwidth, precision.
write(1, "\n"BLUE"[X conversion]"RESET"\n", 28);
	i = -1;
	while (++i < 3)
		diffintegers("%X", (void *)(ULONG_MAX - 1 + i));
	
// write(1, "\n"BLUE"[BONUS: di conversion]"RESET"\n", 29);
// 	testinteger();
	return (0);
}
<<<<<<< HEAD
=======

void testinteger(void){
	print1argdiff("%-+-d",(void *) 42);
	print1argdiff("%-+-d", (void *)-42);
	print1argdiff("%3d",(void *) 42000);
	print1argdiff("%3d", (void *)-42000);
	print1argdiff("%03i",(void *) 42000);
	print1argdiff("%03i", (void *)-42000);
	print1argdiff("%0+3d",(void *) 42000);
	print1argdiff("%0+3d", (void *)-42000);
	print1argdiff("%0 3d",(void *) 42000);
	print1argdiff("%0 3d", (void *)-42000);
	print1argdiff("%0 +3d",(void *) 42000);
	print1argdiff("%0 +3d", (void *)-42000);
	print1argdiff("%0+ 3d",(void *) 42000);
	print1argdiff("%0+ 3d", (void *)-42000);
	print1argdiff("%-+3d",(void *) 42000);
	print1argdiff("%-+3d", (void *)-42000);
	print1argdiff("%5d",(void *) 42);
	print1argdiff("%5d", (void *)-42);
	print1argdiff("%-5d",(void *) 42);
	print1argdiff("%-5d", (void *)-42);
	print1argdiff("%05d",(void *) 42);
	print1argdiff("%0+5d",(void *) 42);
	print1argdiff("%05d", (void *)-42);
	print1argdiff("% 5d",(void *) 42);
	print1argdiff("% 5d", (void *)-42);
	print1argdiff("%0 5d",(void *) 42);
	print1argdiff("%+0 5d",(void *) 42);
	print1argdiff("%0 5d", (void *)-42);
	print1argdiff("%0-5d",(void *) 42);
	print1argdiff("%+0-5d",(void *) 42);
	print1argdiff("%0-5d", (void *)-42);
	print1argdiff("%+5d",(void *) 42);
	print1argdiff("%+5d", (void *)-42);
	print1argdiff("%0+5d", (void *)-42);
	print1argdiff("%+ 5d",(void *) 42);
	print1argdiff("%+ 5d", (void *)-42);
	print1argdiff("%0+0 5d",(void *) 42);
	print1argdiff("%0+0 5d", (void *)-42);
	print1argdiff("%+ -5d",(void *) 42);
	print1argdiff("%+ -5d", (void *)-42);
	print1argdiff("%+-5d",(void *) 42);
	print1argdiff("%+-5d", (void *)-42);
	print1argdiff("%+0-5d", (void *)-42);
	print1argdiff("%- 5d",(void *) 42);
	print1argdiff("%- 5d", (void *)-42);
	print1argdiff("%+- 5d",(void *) 42);
	print1argdiff("%+- 5d", (void *)-42);
	print1argdiff("%+-0 5d",(void *) 42);
	print1argdiff("%+-0 5d", (void *)-42);
	print1argdiff("% -5d",(void *) 42);
	print1argdiff("% -5d", (void *)-42);
	print1argdiff("%+05d",(void *) 42);
	print1argdiff("%+05d", (void *)-42);
	print1argdiff("% 5i", (void *)-42);
	print1argdiff("%5.3d",(void *) 42);
	print1argdiff("%5.2d", (void *)-42);
	print1argdiff("%5.3d", (void *)-42);
	print1argdiff("%5.4d", (void *)-42);
	print1argdiff("%5.5d", (void *)-42);
	print1argdiff("%5.6d", (void *)-42);
	print1argdiff("%6.4d", (void *)-42);
	print1argdiff("%5.5d",(void *) 42);
	print1argdiff("%5.6d",(void *) 42);
	print1argdiff("%8.6d",(void *) 42);
	print1argdiff("%.5d",(void *) 42);
	print1argdiff("%.d",(void *) 42);
	print1argdiff("%-05.3d",(void *) 42);
	print1argdiff("%5.7d",(void *) 42);
	print1argdiff("%10.5d",(void *) 42);
	print1argdiff("%-10.5d",(void *) 42);
	print1argdiff("%010.5d",(void *) 42);
	print1argdiff("% 10.5d",(void *) 42);
	print1argdiff("%0 10.5d",(void *) 42);
	print1argdiff("%+10.5d",(void *) 42);
	print1argdiff("%+-10.5d",(void *) 42);
	print1argdiff("%- 10.5d",(void *) 42);
	print1argdiff("%+010.5d",(void *) 42);
	print1argdiff("%0+5.d",(void *) 12);
	print1argdiff("% 5.7d",(void *) 42);
	print1argdiff("%-10.5d", (void *)-42);
	print1argdiff("%010.5d", (void *)-42);
	print1argdiff("%+10.5d", (void *)-42);
	print1argdiff("% 10.5d", (void *)-42);
	print1argdiff("%+-10.5d", (void *)-42);
	print1argdiff("%- 10.5d", (void *)-42);
	print1argdiff("%+010.5d", (void *)-42);
	print1argdiff("%0 8.6d", (void *)-42);
	print1argdiff("%0 8.6d",(void *) 42);
	print1argdiff("%0+8.6d",(void *) 42);
	print1argdiff("%0+8.6d", (void *)-42);
	print1argdiff("%0 8.6d",(void *) 42000);
	print1argdiff("%0 8.6d", (void *)-42000);
	print1argdiff("%0 8.7d", (void *)-42000);
	print1argdiff("%0+8.7d",(void *) 42000);
	print1argdiff("%0+8.7d", (void *)-42000);
	print1argdiff("%-3.7d", (void *)-42000);
	print1argdiff("%.7d",(void *) 42000);
	print1argdiff("%+.7d", (void *)-42000);
	print1argdiff("%+.7d",(void *) 42000);
	print1argdiff("%+.003d", (void *)-42000);
	print1argdiff("%+.d", (void *)-42000);
	print1argdiff("%07.d",(void *) 42000);
	print1argdiff("%0 10.5d", (void *)-42);
	print1argdiff("%010.d", (void *)-2147483648);
	print1argdiff("%.11i", (void *)-2147483648);
	print1argdiff("%15.12d", (void *)-2147483648);
	print1argdiff("%-15.12d", (void *)-2147483648);
	print1argdiff("%015d", (void *)-2147483648);
	print1argdiff("%015.12d", (void *)-2147483648);
	print1argdiff("%0 10.5d",(void *) 0);
	print1argdiff("%0+5d",(void *) 0);
	print1argdiff("%0+5.d",(void *) 0);
	print1argdiff("%0 5.i",(void *) 0);
	print1argdiff("%-+5.d",(void *) 0);
	print1argdiff("%-3.d",(void *) 0);
	print1argdiff("%- 5.d",(void *) 0);
	print1argdiff("%+.d",(void *) 0);
	print1argdiff("%1.d",(void *) 0);
	print1argdiff("%.d",(void *) 0);
	print1argdiff("% .d",(void *) 0);
	print1argdiff("% 5.3d",(void *) 0);
	print1argdiff("%0+5.3d",(void *) 0);
	print1argdiff("%-+5.3d",(void *) 0);
	print1argdiff("%3d",(void *) 0);
	print1argdiff("%-3d",(void *) 0);
	print1argdiff("% 5.7d", (void *)-420000000);
	print1argdiff("%+5.7d", (void *)-420000000);
	print1argdiff("%+5.7d", (void *)-2147483648);
	print1argdiff("% 5.7d", (void *)-2147483648);
	print1argdiff("% +5.7d", (void *)-2147483648);
	print1argdiff("%+.003d", (void *)-42000);
	print1argdiff("%+ .003d", (void *)-2147483648);
	print1argdiff("%+.d", (void *)-2147483648);
	print1argdiff("%.d", (void *)-2147483648);
	print1argdiff("%0+3d",(void *) 42000);
	print1argdiff("%0 +3d", (void *)-42000);
	print1argdiff("%0 3d", (void *)-42000);
}
/*
make bonus && cc tester_bonus.c libftprintf.a -o printf && ./printf
*/
>>>>>>> fda5e6c (added length modifier, everything done until getting length and printing list)
