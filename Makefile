NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar -r -c -s
RM = rm -rf

ifndef BONUS
    SRC_NAME = ft_printf
else
    PRE_SRC = ft_printf_bonus
    SRC_NAME = $(foreach item, $(PRE_SRC), ./bonus/$(item))
endif

SRC = $(foreach item, $(SRC_NAME), $(item).c)
OBJ = $(foreach item, $(SRC_NAME), $(item).o)

$(NAME):
	$(CC) $(CFLAGS) -o $(OBJ) -c $(SRC)
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