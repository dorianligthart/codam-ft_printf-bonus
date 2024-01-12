NAME    = libftprintf.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude
AR      = ar -r -c -s
RM      = rm -rf

LIBFT   = ./libft/
# LIBFT_H = ./libft/libft.h

MAN_SRC = ./src/ft_printf.c
MAN_OBJ = ./src/ft_printf.o

BON_SRC = ./src/bonus/ft_getlength_bonus.c ./src/bonus/ft_initstructs_bonus.c\
          ./src/bonus/ft_printcomp_bonus.c ./src/bonus/ft_printf_bonus.c
BON_OBJ = $(addsuffix .o, $(basename $(BON_SRC)))

ifdef BONUS
    SRC = $(BON_SRC)
    OBJ = $(BON_OBJ)
else
    SRC = $(MAN_SRC)
    OBJ = $(MAN_OBJ)
endif

$(NAME):
	make -C $(LIBFT)
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