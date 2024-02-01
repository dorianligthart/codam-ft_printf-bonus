SRC_NAMES  = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_longlen.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_varray.c 
MAN_NAMES  = ft_printf.c
BON_NAMES  = ft_printf_bonus.c ft_getlen_bonus.c ft_pflist_bonus.c ft_structs_bonus.c

SRC_SRC    = $(addprefix src/, $(SRC_NAMES))
MAN_SRC    = $(addprefix src/, $(MAN_NAMES))
BON_SRC    = $(addprefix src/bonus/, $(BON_NAMES))

OBJ_MAN    = $(SRC_NAMES:%.c=%.o) $(MAN_NAMES:%.c=%.o)
OBJ_BON    = $(SRC_NAMES:%.c=%.o) $(BON_NAMES:%.c=%.o)

NAME       = libftprintf.a
CC         = cc
CFLAGS     = -Wall -Wextra -Werror -g -DDEBUG=1
AR         = ar -r -c -s
INCLUDE    = -Iinclude
BUILD      = build/

$(NAME): fclean
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC_SRC) $(MAN_SRC)
	mv -f $(OBJ_MAN) $(BUILD)
	$(AR) $(NAME) $(addprefix $(BUILD), $(OBJ_MAN))
all: $(NAME)
bonus: fclean
	mkdir -p $(BUILD)
	$(CC) -c $(CFLAGS) $(INCLUDE) $(SRC_SRC) $(BON_SRC)
	mv -f $(OBJ_BON) $(BUILD)
	$(AR) $(NAME) $(addprefix $(BUILD), $(OBJ_BON))
clean:
	rm -f $(OBJ_MAN) $(OBJ_BON) $(addprefix $(BUILD), $(OBJ_MAN)) $(addprefix $(BUILD), $(OBJ_BON))
	rm -df $(BUILD)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all bonus clean fclean re
