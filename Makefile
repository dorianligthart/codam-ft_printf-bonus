#release:
CC     := cc
COMMON :=-Wno-sign-compare -Wno-implicit-fallthrough -Wall -Wextra -Werror -DIEEE_8087 -DNO_ERRNO
CFLAGS :=$(COMMON) -c
LFLAGS :=$(COMMON) -L. -l:libftprintf.a -ggdb -fsanitize=address
HEADER := printf.h
BUILD  := objfiles/
SRC := dtoa.c libft.c ft_sizelen.c ft_ssizelen.c printf.c vprintf.c\
	   pf_format_to_data.c pf_misc.c pf_signed.c pf_unsigned.c pf_double.c
OBJ := $(SRC:.c=.o)
$(BUILD)%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

NAME := libftprintf.a
$(NAME): $(addprefix $(BUILD), $(OBJ))
	ar rcs $@ $^
$(BUILD):
	mkdir -p $(BUILD)
all: $(BUILD) $(HEADER) $(NAME)
bonus: all
clean:
	rm -f $(addprefix $(BUILD), $(OBJ))
	rm -f $(NAME_TEST)
	rm -fd $(BUILD)
fclean: clean
	rm -f $(NAME)
re: fclean
	sleep 0.2 && make all #sleep because rm thread isn't finished

# test/debug:
NAME_TEST := test.out
test:
	$(CC) main.c -o $(NAME_TEST) $(LFLAGS) $(NAME)
tags:
	ctags -R ./*

.PHONY: all bonus clean fclean re test tags
