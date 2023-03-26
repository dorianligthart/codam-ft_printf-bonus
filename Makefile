NAME			= libftprintf.a
CC				= cc
CFLAGS			= -Wall, -Wextra -Werror -I ft_printf.h

SRCNAMES		= printf atoi itoa_base strlen
PRE_SRC			= $(addprefix ./src/ft_, ${SRCNAMES})
SRC				= $(addsuffix .c, ${P_SRC})

SRCNAMES_BONUS	=


OBJFILES		= $(SRC:%.c=%.o)
OBJFILES_BONUS	= $(SRC_BONUS:%.c=%.o)

ifdef BON
OBJ = $(OBJFILES) $(OBJFILES_BONUS)
else
OBJ = $(OBJFILES)
endif

all: $(NAME)
$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(NAME) $(OBJ)
bonus: 
	make all BON=1
clean:
	rm -f $(OBJ_BONUS) $(OBJ)
fclean:
	rm -f $(NAME)
re:
	clean fclean

.PHONY all bonus clean fclean re