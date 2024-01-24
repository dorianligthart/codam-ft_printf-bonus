NAME     = libftprintf.a
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -c
AR       = ar -r -c -s
INCLUDE  = -Iinclude
MAN_PATH = ./src/
BON_PATH = ./src/printfbonus/
BUILD    = ./build/

LIB_NAMES =\
    ft_atoi.c\
    ft_bzero.c\
    ft_calloc.c\
    ft_isalnum.c\
    ft_isalpha.c\
    ft_isascii.c\
    ft_isdigit.c\
    ft_isprint.c\
    ft_itoa.c\
    ft_longlen.c\
    ft_lstadd_back.c\
    ft_lstadd_front.c\
    ft_lstclear.c\
    ft_lstdelone.c\
    ft_lstiter.c\
    ft_lstlast.c\
    ft_lstmap.c\
    ft_lstnew.c\
    ft_lstsize.c\
    ft_memchr.c\
    ft_memcmp.c\
    ft_memcpy.c\
    ft_memmove.c\
    ft_memset.c\
    ft_putchar_fd.c\
    ft_putendl_fd.c\
    ft_putnbr_fd.c\
    ft_putstr_fd.c\
    ft_split.c\
    ft_strchr.c\
    ft_strdup.c\
    ft_striteri.c\
    ft_strjoin.c\
    ft_strlcat.c\
    ft_strlcpy.c\
    ft_strlen.c\
    ft_strmapi.c\
    ft_strncmp.c\
    ft_strnstr.c\
    ft_strrchr.c\
    ft_strtrim.c\
    ft_substr.c\
    ft_tolower.c\
    ft_toupper.c\
    ft_varray.c

MAN_NAMES = ft_printf.c
BON_NAMES = ft_printf_bonus.c\
    ft_structs_bonus.c\
    ft_getlength_bonus.c\
    ft_comp_bonus.c

LIB_SRC  = $(addprefix $(MAN_PATH),    $(LIB_NAME))
MAN_SRC  = $(addprefix $(MAN_PATH),    $(MAN_NAME))
BON_SRC  = $(addprefix $(BON_PATH),    $(BON_NAME))

LIB_OBJ  = $(addsuffix .o,  $(basename $(LIB_NAME)))
MAN_OBJ  = $(addsuffix .o,  $(basename $(MAN_NAME)))
BON_OBJ  = $(addsuffix .o,  $(basename $(BON_NAME)))

ifdef BONUS
    SRC  = $(LIB_SRC) $(BON_SRC)
    OBJ  = $(LIB_OBJ) $(BON_OBJ)
else
    SRC  = $(LIB_SRC) $(MAN_SRC)
    OBJ  = $(LIB_OBJ) $(MAN_OBJ)
endif

DST_PATH = $(addprefix $(BUILD), $(OBJ))
RM_ALL_OBJ = $(addprefix $(BUILD), $(LIB_OBJ) $(MAN_OBJ) $(BON_OBJ))

$(NAME):
	mkdir -p $(BUILD)
#	echo $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC)
	@mv $(OBJ) $(BUILD)
	@$(AR) $(NAME) $(DST_PATH)
all: $(NAME)
bonus:
	make fclean
	make all BONUS=1
clean:
	rm -f  $(RM_ALL_OBJ)
	rm -df $(BUILD)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re