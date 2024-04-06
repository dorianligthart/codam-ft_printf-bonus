SRC =\
	pf_libft.c\
	pf_printf.c\
	pf_vprintf.c\
	pf_conversion.c\
	pf_conv_misc.c\
	pf_conv_signed.c\
	pf_conv_unsigned.c\
	pf_conv_double.c

OBJ = $(addsuffix .o, $(basename $(SRC)))

NAME = libftprintf.a
CFLAGS = -c -I./ -Wall -Wextra -fsanitize=address -ggdb

$(NAME):
	cc $(CFLAGS) $(SRC)
	ar rcs $(NAME) $(OBJ)

all: $(NAME)
bonus: $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean $(NAME)

.PHONY: $(NAME) all bonus clean fclean re
