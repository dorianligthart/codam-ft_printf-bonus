NAME    = libftprintf.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar -r -c -s
RM      = rm -rf

ifdef BONUS
    SRC = ./bonus/*.c
    OBJ = $(addsuffix .o, $(basename $(SRC)))
else
    SRC = ft_printf.c
    OBJ = ft_printf.o
endif

$(NAME):
	$(CC) $(CFLAGS) -c $(SRC)
	$(AR) libftprintf.a $(OBJ)
all: $(NAME)
bonus: fclean
	make all BONUS=1
clean:
	$(RM) $(OBJ)
fclean:
	$(RM) $(OBJ) libftprintf.a
re: fclean all

.PHONY: all clean fclean re