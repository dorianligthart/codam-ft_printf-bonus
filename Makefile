SRC =\
	pf_libft.c\
	pf_printf.c\
	pf_vprintf.c\
	pf_conversion.c\
	pf_conversion_char.c\
	pf_conversion_signed.c\
	pf_conversion_unsigned.c\
	pf_conversion_double.c

OBJ = $(addsuffix .o, $(basename $(SRC)))

NAME = libftprintf.a
CFLAGS = -c -I./ -Wall -Wextra

$(NAME):
	@cc $(CFLAGS) $(SRC)
	@ar rcs $(NAME) $(OBJ)

all: $(NAME)
bonus: $(NAME)
clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean $(NAME)

.PHONY: $(NAME) all bonus clean fclean re
