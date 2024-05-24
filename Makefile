NAME = libftprintf.a
NAME_TEST = a.out
CC = cc
CFLAGS = -Wall -Wextra -g
BUILD = ./build/
HEADER = printf.h
SRC = libft.c ft_sizelen.c ft_ssizelen.c\
	printf.c\
	vprintf.c\
	pf_format_to_data.c\
	pf_misc.c\
	pf_signed.c\
	pf_unsigned.c\
	pf_double.c

OBJ = $(addsuffix .o, $(basename $(SRC)))
BUILD_OBJ = $(addprefix $(BUILD), $(OBJ))

$(BUILD)%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD):
	mkdir -p $(BUILD)

$(NAME): $(BUILD) $(HEADER) $(BUILD_OBJ)
	ar rcs $(NAME) $(BUILD_OBJ)

all: $(NAME)
bonus: $(NAME)
clean:
	rm -f $(BUILD_OBJ)
	rm -fd $(BUILD)
fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_TEST)
re: fclean $(NAME)
test: 
	$(CC) main.c -o $(NAME_TEST) -L. -l:libftprintf.a -g -fsanitize=address

.PHONY: $(NAME) all bonus clean fclean re test main