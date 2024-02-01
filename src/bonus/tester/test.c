/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:33:57 by rde-brui          #+#    #+#             */
/*   Updated: 2024/01/24 16:44:14 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv)
{
	print_full_width('-');

	if (argc == 1)
	{
		markup("\n\nMandatory", 1, 36, 0);
		chr();
		str();
		integer();
		unsigned_int();
		small_x();
		big_x();
		void_ptr();
		percentage_char();

		markup("\n\nBonus", 1, 36, 0);
		chr_bns();
		str_bns();
		d_bns();
		u_bns();
		x_bns();
		X_bns();
		ptr_bns();
	}
	else
	{
		int i = 1;
		while (i < argc)
		{
			if (strcmp(argv[i], "chr") == 0)
				chr();
			else if (strcmp(argv[i], "str") == 0)
				str();
			else if (strcmp(argv[i], "int") == 0)
				integer();
			else if (strcmp(argv[i], "u") == 0)
				unsigned_int();
			else if (strcmp(argv[i], "x") == 0)
				small_x();
			else if (strcmp(argv[i], "X") == 0)
				big_x();
			else if (strcmp(argv[i], "ptr") == 0)
				void_ptr();
			else if (strcmp(argv[i], "%") == 0)
				percentage_char();
			else if (strcmp(argv[i], "bchr") == 0)
				chr_bns();
			else if (strcmp(argv[i], "bstr") == 0)
				str_bns();
			else if (strcmp(argv[i], "bint") == 0)
				d_bns();
			else if (strcmp(argv[i], "bu") == 0)
				u_bns();
			else if (strcmp(argv[i], "bx") == 0)
				x_bns();
			else if (strcmp(argv[i], "bX") == 0)
				X_bns();
			else if (strcmp(argv[i], "bptr") == 0)
				ptr_bns();
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}

int	capture_output(int (*func)(const char *, va_list), char *output_buffer,
											const char *text, va_list start)
{
	int	pipe_fd[2];
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe() failed");
		exit(EXIT_FAILURE);
	}

	int	stdout_copy = dup(fileno(stdout));
	dup2(pipe_fd[1], fileno(stdout));
	close(pipe_fd[1]);

	int total_charachters = func(text, start);
	fflush(stdout);

	dup2(stdout_copy, fileno(stdout));
	close(stdout_copy);
	ssize_t	nbytes = read(pipe_fd[0], output_buffer, 10239);
	if (nbytes > 0)
		output_buffer[nbytes] = '\0';
	else if (nbytes == 0)
		output_buffer[nbytes] = '\0';
	else
	{
		perror("read() failed or no data read");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	return (total_charachters);
}

void	testing(short int test_index, const char *text, ...)
{
	va_list		start;
	char		printf_output[10240] = {0};
	char		ft_printf_output[10240] = {0};
	int			og_number;
	int			my_number;
	char		*print_return;
	short		text_num;
	// short		fail = 0;

	va_start(start, text);
	og_number = capture_output(vprintf, printf_output, text, start);
	va_end(start);

	va_start(start, text);
	my_number = capture_output(fft_printf, ft_printf_output, text, start);
	va_end(start);
	
	if (TEXT_ONLY)
		text_num = (strcmp(printf_output, ft_printf_output) == 0 && og_number == my_number);
	else
		text_num = (strcmp(printf_output, ft_printf_output) == 0);
	if (text_num > 0) {
		if (SHOWCASE == true)
		{
			printf("\033[1;32m%d.OK ----->\033[0m\n", test_index);
			printf("\033[42m \033[0m\033[37m%s\033[0m\033[42m \033[0m\n", printf_output);
			if (NUM)
			{
				print_return = tester_itoa(og_number);
				markup(print_return, 32, 0);
				printf("\n\n");
				free(print_return);
			}
			printf("\033[42m \033[0m\033[37m%s\033[0m\033[42m \033[0m\n", ft_printf_output);
			if (NUM)
			{
				print_return = tester_itoa(my_number);
				markup(print_return, 32, 0);
				printf("\n");
				free(print_return);
			}
		}
		else
		{
			printf("\033[1;32m%d.OK \033[0m", test_index);
			fflush(stdout);
		}
	 } else {
		// fail++;
		printf("\033[1;31m%d.FAIL ----->\033[0m\n", test_index);
		printf("\033[42m \033[0m\033[37m%s\033[0m\033[42m \033[0m\n", printf_output);
		print_return = tester_itoa(og_number);
		markup(print_return, 32, 0);
		printf("\n\n");
		free(print_return);
		printf("\033[41m \033[0m\033[37m%s\033[0m\033[41m \033[0m\n", ft_printf_output);
		print_return = tester_itoa(my_number);
		if (og_number == my_number)
			markup(print_return, 32, 0);
		else
			markup(print_return, 2, 31, 0);
		free(print_return);
		printf("\n");
	}
	fflush(stdout);
	// return (fail);
}

void	chr(void)
{
	char	*text = "%c = %d";
	short	index = 1;
	char	chr = 'A';

	markup("\nChar check\n", 1, 35, 0);
	testing(index++, text, chr, chr);
	chr = '\n';
	testing(index++, text, chr, chr);
	chr = 'Z';
	testing(index++, text, chr, chr);
	chr = '\0';
	testing(index++, text, chr, chr);
	chr = '0';
	testing(index++, text, chr, chr);
	// chr = 'c' + 256;
	// testing(index++, text, chr, chr);

	testing(index++, "og .%c|", 0);

	testing(index++, text, 0);
	text = " %c %c %c ";
	testing(index++, text, '0', 0, '1');
	testing(index++, text, '2', '1', 0);

}

void	str(void)
{
	const char	*text = "%s";
	short		index = 1;
	char		*str = "Z";

	markup("\nString check\n", 1, 35, 0);

	testing(index++, text, str);
	str = "a beautiful day";
	testing(index++, text, str);
	str = "First\0";
	testing(index++, text, str);
	str = "2words\0another word";
	testing(index++, text, str);
	str = 0;
	testing(index++, text, str);
	str = NULL;
	testing(index++, text, str);
	str = "";
	testing(index++, text, str);
}


void	integer(void)
{
	const char	*text = "%d";
	short		index = 1;
	int			nbr = 0;
	long int	lnbr = -98754648912;

	markup("\nInteger check\n", 1, 35, 0);
	testing(index++, text, nbr);
	nbr = INT_MAX;
	testing(index++, text, nbr);
	nbr = INT_MIN;
	testing(index++, text, nbr);
	
	testing(index++, text, lnbr);

	text = " %d ";
	nbr = 0;
	testing(index++, text, nbr);
	nbr = INT_MAX;
	testing(index++, text, nbr);
	nbr = INT_MIN;
	testing(index++, text, nbr);
	lnbr = -98754648912;
	testing(index++, text, lnbr);
	text = " %d %d ";
	nbr = 1;
	testing(index++, text, nbr, nbr + 123123212);
	nbr = INT_MAX;
	testing(index++, text, nbr, nbr / 2);
	nbr = INT_MIN;
	testing(index++, text, nbr, nbr);
	lnbr = -98754648912;
	testing(index++, text, lnbr, nbr);
}

void	unsigned_int(void)
{
	const char		*text = "%u";
	short			index = 1;
	unsigned int	nbr = 0;
	markup("\nUnsigned integer check\n", 1, 35, 0);

	testing(index++, text, nbr);
	nbr = -1;
	testing(index++, text, nbr);
	nbr = UINT_MAX;
	testing(index++, text, nbr);

	// long int lnbr = -98754648912;
	// testing(index++, text, lnbr);
}

void	small_x(void)
{
	const char		*text = "%x";
	short			index = 1;
	unsigned int	nbr = 0;

	markup("\nx check\n", 1, 35, 0);
	testing(index++, text, nbr);
	nbr = -1;
	testing(index++, text, nbr);
	nbr = UINT_MAX;
	testing(index++, text, nbr);
	nbr = 99999999;
	testing(index++, text, nbr);
	nbr = 177;
	testing(index++, text, nbr);
	nbr = 8866662;
	testing(index++, text, nbr);
}

void	big_x(void)
{
	const char		*text = "%X";
	short			index = 1;
	unsigned int	nbr = 0;

	markup("\nX check\n", 1, 35, 0);
	testing(index++, text, nbr);
	nbr = -1;
	testing(index++, text, nbr);
	nbr = UINT_MAX;
	testing(index++, text, nbr);
	nbr = 99999999;
	testing(index++, text, nbr);
	nbr = 177;
	testing(index++, text, nbr);
	nbr = 8866662;
	testing(index++, text, nbr);
}

void	void_ptr(void)
{
	const char	*text = "%p";
	short		index = 1;

	markup("\nPointer check\n", 1, 35, 0);
	char	*str1 = "";
	testing(index++, text, str1);
	char	*str2 = "HELLO";
	testing(index++, text, str2);
	char	*str3 = "A";
	testing(index++, text, str3);
	char	*str4 = "qwertyuioplkjhgfdsazxcvbnmmQWERTYUIOPLKJHGFDSAZXCVBNM";
	testing(index++, text, str4);
	unsigned long big_num = 4294967295;
	testing(index++, text, big_num);
	unsigned long long bigger_num = 9223372036854775807;
	testing(index++, text, bigger_num);
	long	number = LONG_MIN;
	testing(index++, text, number);

	testing(index++, text, LONG_MIN, LONG_MAX);
	testing(index++, text, ULONG_MAX, -ULONG_MAX);
	// printf("\n%d", printf("%p", LONG_MIN));			// warning
	// ft_printf("\n%d", ft_printf("%p", LONG_MIN));
	if (NIL)
	{
		testing(index++, "%p", LONG_MIN);
		char	*str5 = 0;
		testing(index++, text, str5);
		char	*str6 = NULL;
		testing(index++, text, str6);
	}
}

void	percentage_char(void)
{
	const char		*text = "%s";
	short			index = 1;
	char			*str = "%";

	markup("\npercentage_char\n", 1, 35, 0);
	testing(index++, text, str);
	str = "%\%";
	testing(index++, text, str);
	str = "%\%%";
	testing(index++, text, str);
	str = "%\%%%";
	testing(index++, text, str);
	str = "%Qoke\n";
	testing(index++, text, str);
	str = "%0";
	testing(index++, text, str);
	str = "%%%%PL\n";
	testing(index++, text, str);
	str = "%%%%%Ba\n";
	testing(index++, text, str);
	str = "%%%%%Ze%";
	testing(index++, text, str);
}

void	chr_bns(void)
{
	short		index = 1;

	markup("\nChar Bonus\n", 1, 35, 0);
	testing(index++, "%-c", 'Z');
	testing(index++, "%-1c", 'Z');
	testing(index++, "%-2c", 'Z');
	testing(index++, " %-0c ", 'Z');
	testing(index++, "-- %15c --", 'Z');
	testing(index++, "here %c more to %c in %c", 'Z', 'C', 'P');
	testing(index++, "%--12c%c", 'Z', 'A');
	testing(index++, " %6cK %-c ", 'Z', 'A');			//	11
	testing(index++, " %6cK %-c ", 'Z', 'A');			//	11
	testing(index++, "%6cK %-6cK", 'Z', 'A');	//	15
	testing(index++, "%-6cK %6c", 'Z', 'A');	//	14
	testing(index++, "%6cK %-2cX", 'Z', 'A');	//	11
	testing(index++, "%6cK %-cX", 'Z', 'A');	//	10
	testing(index++, " %6cK %-cX %------cX %-----11cX ", 'Z', 'A', 'B', 'P');	//	28
	testing(index++, " %6cK %-cX %------cX %11cX ", 'Z', 'A', 'B', 'P');	//	28
	}

void	str_bns(void)
{
	short		index = 1;

	markup("\nString Bonus\n", 1, 35, 0);
	testing(index++, "%-15s", "ZXCVBNM");	//	16
	testing(index++, "%15s", "str");	//	23
	testing(index++, "%-21s", "WOOP");	//	24
	testing(index++, "%-15s|%-12s", "str", "What happened over here?");	//	50
	testing(index++, "%-15s|%-21s", "str", "0");	//	47
	testing(index++, "%10.5s", "abcdefghijklmnop");	//	11
	testing(index++, "%-10.5s", "abcdefghijklmnop");	//	11
	testing(index++, "%-10.s", "abcdefghijklmnop");	//	11
	testing(index++, "%-10s", "abcdefghijklmnop");		//	17
	testing(index++, "%-.10s", "abcdefghijklmnop");		//	11
	testing(index++, "%.10s", "abcdefghijklmnop");		//	11

	testing(index++, "%15s", (char *)NULL);
	testing(index++, "%-12s", (char *)NULL);
	testing(index++, "%4s", (char *)NULL);
	testing(index++, "%10.6s", (char *)NULL);	//	11
	testing(index++, " %.10s", (char *)NULL);		//	8
	testing(index++, "%-10s", (char *)NULL);		//	11
	testing(index++, "%-.10s", (char *)NULL);		//	7
	
	if (NIL)
	{
		testing(index++, "%10.5s|%10.5s", (char *)NULL, "abcdefghijklmnop");	//	23
		testing(index++, "%-.5s", (char *)NULL);		//	1
		testing(index++, "%10.5s", (char *)NULL);	//	11
		testing(index++, "%10.5s|%10.5s", (char *)NULL, "abcdefghijklmnop");	//	23
		testing(index++, "%-15s|%-15s|%-12s|%10.5s|%-.10s", "ZXCVBNM", (char *)NULL, "What happened over here?", (char *)NULL, (char *)NULL);
	}
	
	//	// printf("%.-10s|", "abcdefghijklmnop");	// invalid, warning
}

void	d_bns(void)
{
	markup("\nDex / Int Bonus\n", 1, 35, 0);
	testing(1, "%-+-d", 42);
	testing(2, "%-+-d", -42);
	testing(3, "%3d", 42000);
	testing(4, "%3d", -42000);
	testing(5, "%03i", 42000);
	testing(6, "%03i", -42000);
	testing(7, "%0+3d", 42000);
	testing(8, "%0+3d", -42000);
	testing(9, "%0 3d", 42000);
	testing(10, "%0 3d", -42000);
	testing(11, "%0 +3d", 42000);
	testing(12, "%0 +3d", -42000);
	testing(13, "%0+ 3d", 42000);
	testing(14, "%0+ 3d", -42000);
	testing(15, "%-+3d", 42000);
	testing(16, "%-+3d", -42000);
	testing(17, "%5d", 42);
	testing(18, "%5d", -42);
	testing(19, "%-5d", 42);
	testing(20, "%-5d", -42);
	testing(21, "%05d", 42);
	testing(22, "%0+5d", 42);
	testing(23, "%05d", -42);
	testing(24, "% 5d", 42);
	testing(25, "% 5d", -42);
	testing(26, "%0 5d", 42);
	testing(27, "%+0 5d", 42);
	testing(28, "%0 5d", -42);
	testing(29, "%0-5d", 42);
	testing(30, "%+0-5d", 42);
	testing(31, "%0-5d", -42);
	testing(32, "%+5d", 42);
	testing(33, "%+5d", -42);
	testing(34, "%0+5d", -42);
	testing(35, "%+ 5d", 42);
	testing(36, "%+ 5d", -42);
	testing(37, "%0+0 5d", 42);
	testing(38, "%0+0 5d", -42);
	testing(39, "%+ -5d", 42);
	testing(40, "%+ -5d", -42);
	testing(41, "%+-5d", 42);
	testing(42, "%+-5d", -42);
	testing(43, "%+0-5d", -42);
	testing(44, "%- 5d", 42);
	testing(45, "%- 5d", -42);
	testing(46, "%+- 5d", 42);
	testing(47, "%+- 5d", -42);
	testing(48, "%+-0 5d", 42);
	testing(49, "%+-0 5d", -42);
	testing(50, "% -5d", 42);
	testing(51, "% -5d", -42);
	testing(52, "%+05d", 42);
	testing(53, "%+05d", -42);
	testing(54, "% 5i", -42);
	testing(55, "%5.3d", 42);
	testing(56, "%5.2d", -42);
	testing(57, "%5.3d", -42);
	testing(58, "%5.4d", -42);
	testing(59, "%5.5d", -42);
	testing(60, "%5.6d", -42);
	testing(61, "%6.4d", -42);
	testing(62, "%5.5d", 42);
	testing(63, "%5.6d", 42);
	testing(64, "%8.6d", 42);
	testing(65, "%.5d", 42);
	testing(66, "%.d", 42);
	testing(67, "%-05.3d", 42);
	testing(68, "%5.7d", 42);
	testing(69, "%10.5d", 42);
	testing(70, "%-10.5d", 42);
	testing(71, "%010.5d", 42);
	testing(72, "% 10.5d", 42);
	testing(73, "%0 10.5d", 42);
	testing(74, "%+10.5d", 42);
	testing(75, "%+-10.5d", 42);
	testing(76, "%- 10.5d", 42);
	testing(77, "%+010.5d", 42);
	testing(78, "%0+5.d", 12);
	testing(79, "% 5.7d", 42);
	testing(80, "%-10.5d", -42);
	testing(81, "%010.5d", -42);
	testing(82, "%+10.5d", -42);
	testing(83, "% 10.5d", -42);
	testing(84, "%+-10.5d", -42);
	testing(85, "%- 10.5d", -42);
	testing(86, "%+010.5d", -42);
	testing(87, "%0 8.6d", -42);
	testing(88, "%0 8.6d", 42);
	testing(89, "%0+8.6d", 42);
	testing(90, "%0+8.6d", -42);
	testing(91, "%0 8.6d", 42000);
	testing(92, "%0 8.6d", -42000);
	testing(93, "%0 8.7d", -42000);
	testing(94, "%0+8.7d", 42000);
	testing(95, "%0+8.7d", -42000);
	testing(96, "%-3.7d", -42000);
	testing(97, "%.7d", 42000);
	testing(98, "%+.7d", -42000);
	testing(99, "%+.7d", 42000);
	testing(100, "%+.003d", -42000);
	testing(101, "%+.d", -42000);
	testing(102, "%07.d", 42000);
	testing(103, "%0 10.5d", -42);
	testing(104, "%010.d", -2147483648);
	testing(105, "%.11i", -2147483648);
	testing(106, "%15.12d", -2147483648);
	testing(107, "%-15.12d", -2147483648);
	testing(108, "%015d", -2147483648);
	testing(109, "%015.12d", -2147483648);
	testing(110, "%0 10.5d", 0);
	testing(111, "%0+5d", 0);
	testing(112, "%0+5.d", 0);
	testing(113, "%0 5.i", 0);
	testing(114, "%-+5.d", 0);
	testing(115, "%-3.d", 0);
	testing(116, "%- 5.d", 0);
	testing(117, "%+.d", 0);
	testing(118, "%1.d", 0);
	testing(119, "%.d", 0);
	testing(120, "% .d", 0);
	testing(121, "% 5.3d", 0);
	testing(122, "%0+5.3d", 0);
	testing(123, "%-+5.3d", 0);
	testing(124, "%3d", 0);
	testing(125, "%-3d", 0);
	testing(126, "% 5.7d", -420000000);
	testing(127, "%+5.7d", -420000000);
	testing(128, "%+5.7d", -2147483648);
	testing(129, "% 5.7d", -2147483648);
	testing(130, "% +5.7d", -2147483648);
	testing(131, "%+.003d", -42000);
	testing(132, "%+ .003d", -2147483648);
	testing(133, "%+.d", -2147483648);
	testing(134, "%.d", -2147483648);
	testing(135, "%0+3d", 42000);
	testing(136, "%0 +3d", -42000);
	testing(137, "%0 3d", -42000);
	testing(138, " %+5.7d %-3d %0 10.5d %.5d %.d %+-0 5d", -2147483648, 0, -42, 42, 42, -42);

	// printf("%5. 2d!\n", 42);				//	-Wall -Werror -Wextra doesn't work
	// printf("%5.-2d!", 42);				//	-Wall -Werror -Wextra doesn't work
}

void	u_bns(void)
{
	short		index = 1;

	markup("\nu Bonus\n", 1, 35, 0);
	testing(index++, "%-10u", 0xFFFFFFFF);
	testing(index++, "%-010u", 42);
	testing(index++, "%010u", 42);
	testing(index++, "%-10.5u", 42);
	testing(index++, "%010.5u", 42);
	testing(index++, "%.2u", 42345);
	testing(index++, "%5u", 0);
	testing(index++, "%05u", 0);
	testing(index++, "%5.u", 0);
	testing(index++, "%0-10u", 42);
	testing(index++, "%-+-u", 42);
	testing(index++, " %-10u %-010u %010u %-10.5u %010.5u %.2u %5.u %05u ", 0xFFFFFFFF, 42, 42, 42, 42345, 0, 0, 0);
}

void	x_bns(void)
{
	short		index = 1;

	markup("\nx Bonus\n", 1, 35, 0);

	testing(index++, "%#x", 15);
	testing(index++, "%#x", 200);
	testing(index++, "%#x", 9);
	testing(index++, "%#x", 16);
	testing(index++, "%#x", 17);
	testing(index++, "%-10x", 5);
	testing(index++, "%-10x", 0x1A2B3C);
	testing(index++, "%-010x", 0xD0E9F8);
	testing(index++, "%010x", 0xFFFFFFFF);
	testing(index++, "%-10.5x", 42);
	testing(index++, "%010.5x", 42);
	testing(index++, "%.2x", 42345);
	testing(index++, "%5x", 0);
	testing(index++, "%-5x", 0);
	testing(index++, "%05x", 0);
	testing(index++, "%5.x", 0);
	testing(index++, "%-#10.1x", 42);
	testing(index++, "%#-10x", 42);
	testing(index++, "%0#10x", 42);
	testing(index++, "%-#10.5x", 42);
	testing(index++, "%#010.5x", 42);
	testing(index++, "%#.2x", 42345);
	testing(index++, "%#5x", 0);
	testing(index++, "%#-5x", 0);
	testing(index++, "%0#5x", 0);
	testing(index++, "%#5.x", 0);
	testing(index++, "%-#10.1x", 42);
	testing(index++, " %#x ", 0);
	testing(index++, "%#1.x", 0);
	testing(index++, "%#2.x", 0);
	testing(index++, "%#3.x", 0);
	testing(index++, "%0-#10x", 42);
	// testing(index++, " %-10x %-10x %010.5x %05x %-#10.1x %#.2x %#5.x ", 5, 0x1A2B3C, 42, 0, 42, 42345, 0);
}

void	X_bns(void)
{
	short		index = 1;

	markup("\nX Bonus\n", 1, 35, 0);
	testing(index++, "%#X", 15);
	testing(index++, "%#X", 200);
	testing(index++, "%#X", 9);
	testing(index++, "%#X", 16);
	testing(index++, "%#X", 17);
	testing(index++, "%-10X", 5);
	testing(index++, "%-10X", 0x1A2B3C);
	testing(index++, "%-010X", 0xD0E9F8);
	testing(index++, "%010X", 0xFFFFFFFF);
	testing(index++, "%-10.5X", 42);
	testing(index++, "%010.5X", 42);
	testing(index++, "%.2X", 42345);
	testing(index++, "%5X", 0);
	testing(index++, "%-5X", 0);
	testing(index++, "%05X", 0);
	testing(index++, "%5.X", 0);
	testing(index++, "%-#10.1X", 42);
	testing(index++, "%#-10X", 42);
	testing(index++, "%0#10X", 42);
	testing(index++, "%-#10.5X", 42);
	testing(index++, "%#010.5X", 42);
	testing(index++, "%#.2X", 42345);
	testing(index++, "%#5X", 0);
	testing(index++, "%#-5X", 0);
	testing(index++, "%0#5X", 0);
	testing(index++, "%#5.X", 0);
	testing(index++, "%-#10.1X", 42);
	testing(index++, " %#X ", 0);
	testing(index++, "%#1.X", 0);
	testing(index++, "%#1.X", 0);
	testing(index++, "%#2.X", 0);
	testing(index++, "%#3.X", 0);
	testing(index++, "%0-#10X", 42);
	testing(index++, " %-10X %-10X %010.5X %05X %-#10.1X %#.2X %#5.X ", 5, 0x1A2B3C, 42, 0, 42, 42345, 0);
}

void	ptr_bns(void)
{
	short		index = 1;

	markup("\nPointer Bonus\n", 1, 35, 0);
	testing(index++, "%15p", "str");
	testing(index++, "%-21p", INT_MAX);
	testing(index++, "%-8p", INT_MAX);
	testing(index++, "%-15p", "str");
	testing(index++, "%-21p", "0");

	if (NIL)
	{
		testing(index++, "%-10p", NULL);
		testing(index++, "%-15p", NULL);
		testing(index++, "%4p", NULL);
		testing(index++, "%1p", NULL);
		testing(index++, "%6p", NULL);
		testing(index++, "%-6p", NULL);
		testing(index++, "%1p|%-15p|%-12p|%-23p", NULL, "texted", INT_MAX, "a bit of text");
	}
	// // --- if these 2 lines are tested together the second one will faill ---------------------------
	// testing(index++, "%-15s| %s %-12s |", "str", (char *)NULL, "What happened over here?");	//	50
	// testing(index++, "%-15p|%4p|%-21p|", "str", NULL, INT_MAX);
	// //	---------------------------------------------------------------------------------------------
}
