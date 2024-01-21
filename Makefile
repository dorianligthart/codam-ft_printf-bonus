NAME    = libftprintf.a
OBJDIR  = ./obj

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -c
AR      = ar -r -c -s
RM      = rm -rf

MAN_PRE = ft_printf.c
MAN_SRC = $(addprefix ./src/, $(MAN_PRE))
MAN_OBJ = $(addsuffix .o,  $(basename $(MAN_PRE)))

BON_PRE = ft_printf_bonus.c\
          ft_structs_bonus.c\
          ft_getlength_bonus.c\
          ft_comp_bonus.c\
          ft_libftutils_bonus.c
BON_SRC = $(addprefix ./src/bonus/,  $(BON_PRE))
BON_OBJ = $(addsuffix .o,  $(basename $(BON_PRE)))

LIBFTPATH = ./lib/libft/libft.a
LIB       = -I./lib/libft
INCLUDE = -I./include

ifdef BONUS
    SRC = $(BON_SRC)
    OBJ = $(BON_OBJ)
else
    SRC = $(MAN_SRC)
    OBJ = $(MAN_OBJ)
endif


$(NAME):
	make -C ./lib/libft/ bonus
	mv $(LIBFTPATH) ./$(NAME)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) $(LIB)
	mkdir -p $(OBJDIR)
	mv ./$(OBJ) $(OBJDIR)/$(OBJ)
	$(AR) $(NAME) $(OBJDIR)/$(OBJ)
	make -C ./lib/libft/ clean

all: $(NAME)

bonus: fclean	
	make all BONUS=1

clean:
	$(RM) $(OBJDIR)

fclean:
	$(RM) $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re