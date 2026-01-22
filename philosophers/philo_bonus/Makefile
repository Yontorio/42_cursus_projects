COMPILER = cc

COMPILER_FLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes

INCLUDE	= includes/philo_bonus.h

SOURCE_FILES =	srcs/begin.c \
				srcs/butler.c \
				srcs/dinner_cycle.c \
				srcs/philosopher.c \
				srcs/init_clean.c \
				srcs/main.c \
				srcs/one_guest.c \
				srcs/printer.c \
				srcs/errors.c \
				srcs/utils.c

OBJECT_FILES = $(SOURCE_FILES:.c=.o)

NAME = philo_bonus

RM = rm -f

%.o: %.c $(INCLUDE)
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJECT_FILES)
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDES) $(OBJECT_FILES) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJECT_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re