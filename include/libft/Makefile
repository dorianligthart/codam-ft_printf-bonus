NAME    = libft.a
CC      = cc
CFLAGS  = -Wall -Werror -Wextra
RM 	    = rm -f

SRC = \
ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
ft_memchr.c ft_memset.c ft_memcpy.c ft_memmove.c ft_memcmp.c ft_bzero.c\
ft_tolower.c ft_toupper.c ft_atoi.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c\
ft_strlen.c ft_strchr.c ft_strrchr.c ft_striteri.c ft_strmapi.c ft_strncmp.c\
ft_calloc.c ft_itoa.c ft_strdup.c\
ft_strjoin.c ft_strtrim.c ft_substr.c ft_split.c

SRC_BONUS = \
ft_lstnew.c    ft_lstadd_front.c  ft_lstadd_back.c\
ft_lstsize.c   ft_lstlast.c\
ft_lstdelone.c ft_lstclear.c\
ft_lstiter.c   ft_lstmap.c

##	OBJECT CREATION:
OBJ_SRC = $(SRC:%.c=%.o) 
OBJ_SRC_BONUS = $(SRC_BONUS:%.c=%.o)
ifdef BONUS
    OBJ = $(OBJ_SRC) $(OBJ_SRC_BONUS)
else
    OBJ = $(OBJ_SRC) 
endif

##	COMMANDS:
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
all: $(NAME)
bonus:
	make all BONUS=1
clean:
	$(RM) $(OBJ_SRC) $(OBJ_SRC_BONUS)
fclean: clean
	$(RM) $(NAME)
re: fclean $(NAME)
