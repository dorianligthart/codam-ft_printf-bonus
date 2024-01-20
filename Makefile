NAME    = libftprintf.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar -r -c -s
RM      = rm -rf

MAN_PRE = ft_printf.c
MAN_SRC = $(addprefix ./src/, $(MAN_PRE))
MAN_OBJ = $(addsuffix .o, $(basename $(MAN_SRC)))

BON_PRE = ft_printf_bonus.c ft_structs_bonus.c\
          ft_getlength_bonus.c ft_comp_bonus.c\
          ft_libftutils_bonus.c
BON_SRC = $(addprefix ./src/bonus/, $(BON_PRE))
BON_OBJ = $(addsuffix .o, $(basename $(BON_SRC)))

ifdef BONUS
LIBPATH = ./lib/
ARCHIVE = libft/libft.a
    SRC = $(BON_SRC)
    OBJ = $(BON_OBJ)
else
LIBPATH = 
ARCHIVE = 
    SRC = $(MAN_SRC)
    OBJ = $(MAN_OBJ)
endif

$(NAME):
	$(CC) $(CFLAGS) $(LIBPATH)$(ARCHIVE) -c $(SRC)
	$(AR) $(NAME) $(OBJ)
libs:
	make -C $(LIBPATH)
all: libs $(NAME)
bonus: fclean
	make all BONUS=1
clean:
	$(RM) $(MAN_OBJ) $(BON_OBJ)
fclean:
	$(RM) $(MAN_OBJ) $(BON_OBJ) $(NAME)
re: fclean all

.PHONY: all lib clean fclean re