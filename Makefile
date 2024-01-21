NAME    = libftprintf.a
OBJDIR  = ./obj

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar -r -c -s
RM      = rm -rf

MAN_PRE = ft_printf.c
MAN_SRC = $(addprefix ./src/, $(MAN_PRE))
MAN_OBJ = $(addsuffix .o,  $(basename $(MAN_PRE)))

BON_PRE = ft_printf_bonus.c ft_structs_bonus.c\
          ft_getlength_bonus.c ft_comp_bonus.c\
          ft_libftutils_bonus.c
BON_SRC = $(addprefix ./src/bonus/,  $(BON_PRE))
BON_OBJ = $(addsuffix .o,  $(basename $(BON_PRE)))

ifdef BONUS
INCLUDE = -Ift_printf_bonus.h
LIBPATH = ./lib/
ARCHIVE = ./libft/libft.a
    SRC = $(BON_SRC)
    OBJ = $(BON_OBJ)
else
INCLUDE = -Ift_printf.h
LIBPATH = 
ARCHIVE = 
    SRC = $(MAN_SRC)
    OBJ = $(MAN_OBJ)
endif

libs:
	make -C $(LIBPATH)/libft/
	mv $(ARCHIVE) $(NAME)

# mkdir if not exist;
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): | $(OBJDIR)
	$(CC) $(CFLAGS) $(NAME) -o $(OBJDIR)/$(OBJ) -c $(SRC) $(INCLUDE)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)
bonus: libs fclean
	make all BONUS=1
clean:
	$(RM) $(MAN_OBJ) $(BON_OBJ)
fclean:
	$(RM) $(MAN_OBJ) $(BON_OBJ) $(NAME)
re: fclean all

.PHONY: all lib clean fclean re