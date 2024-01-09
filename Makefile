NAME    = libftprintf.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar -r -c -s
RM      = rm -rf

MAN_SRC = ft_printf.c
MAN_OBJ = ft_printf.o

BON_SRC = ./bonus/*.c
BON_OBJ = $(addsuffix .o, $(basename $(BON_SRC)))

ifdef BONUS
    SRC = $(BON_SRC)
    OBJ = $(BON_OBJ)
else
    SRC = $(MAN_SRC)
    OBJ = $(MAN_OBJ)
endif

$(NAME):
	$(CC) $(CFLAGS) -c $(SRC)
	$(AR) $(NAME) $(OBJ)
all: $(NAME)
bonus: fclean
	make all BONUS=1
clean:
	$(RM) $(MAN_OBJ) $(BON_OBJ)
fclean:
	$(RM) $(MAN_OBJ) $(BON_OBJ) $(NAME)
re: fclean all

.PHONY: all clean fclean re