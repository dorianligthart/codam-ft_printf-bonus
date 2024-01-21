NAME    = libftprintf.a
OBJDIR  = ./obj

CC      = cc
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
ifdef BONUS
INCLUDE = -Ift_printf_bonus.h
    SRC = $(BON_SRC)
    OBJ = $(BON_OBJ)
else
INCLUDE = -Ift_printf.h
    SRC = $(MAN_SRC)
    OBJ = $(MAN_OBJ)
endif

$(NAME):
	make -C ./lib/libft/
	mv $(LIBFTPATH) ./$(NAME)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE)
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