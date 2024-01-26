CFLAGS =		-Wall -Werror -Wextra -g #-fsanitize=address
MKDIR_P =		mkdir -p
RM =			rm -f

MISC =			*.out \
				test \
				.DS_Store \
				*.dSYM/

all:	 compile

compile:
	@$(MAKE) -s -C ../
	@cc $(CFLAGS) test.c test_utils.c ../libftprintf.a -o test && ./test

clean:
	$(RM) -r $(MISC)
	$(MAKE) -C ../ clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C ../ fclean

re: fclean all

run:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -o test && ./test

runil:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -D NIL=false -o test && ./test

runtext:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -D TEXT_ONLY=false -o test && ./test

runtextnil:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -D NIL=false -D TEXT_ONLY=false -o test && ./test

show:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -D SHOWCASE=true -o test && ./test

shownum:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -D SHOWCASE=true -D NUM=true -o test && ./test

shownil:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -D SHOWCASE=true -D NIL=false -o test && ./test

shownumnil:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -D SHOWCASE=true -D NUM=true -D NIL=false -o test && ./test

showtext:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -D SHOWCASE=true -D TEXT_ONLY=false -o test && ./test

showtextnil:
	@$(MAKE) -s -C ../
	cc test.c test_utils.c ../libftprintf.a -D SHOWCASE=true -D TEXT_ONLY=false -D NIL=false -o test && ./test

.PHONY: all compile clean fclean re run runil show shownil