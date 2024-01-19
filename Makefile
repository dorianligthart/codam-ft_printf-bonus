include lib/libft

LIBFT_HEADER = libft.h

NAME    = libftprintf.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude
AR      = ar -r -c -s
RM      = rm -rf

MAN_PRE = ft_printf.c
MAN_SRC = $(addprefix ./src/, $(MAN_PRE))
MAN_OBJ = $(addsuffix .o, $(basename $(MAN_SRC)))


BON_PRE = ft_getlength_bonus.c ft_structs_bonus.c ft_comp_bonus.c ft_printf_bonus.c ft_libftutils_bonus.c
BON_SRC = $(addprefix ./src/bonus/, $(BON_PRE))
BON_OBJ = $(addsuffix .o, $(basename $(BON_SRC)))

ifdef BONUS
    SRC = $(BON_SRC)
    OBJ = $(BON_OBJ)
else
    SRC = $(MAN_SRC)
    OBJ = $(MAN_OBJ)
endif

$(NAME):
	$(CC) $(CFLAGS) -c $(SRC) -I$(LIBFT_HEADER)
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