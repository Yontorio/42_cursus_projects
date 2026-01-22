CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_char.c ft_integer.c ft_integer_.c ft_hexa.c ft_hexa_.c ft_pointer.c \
		ft_pointer_.c ft_start.c ft_string.c ft_unsigned.c ft_printf.c

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

ft_printf_HDR = ft_printf.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c $(ft_printf_HDR)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
