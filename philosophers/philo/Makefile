COMPILER = cc

COMPILER_FLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes

INCLUDE	= includes/philo.h

SOURCE_FILES =	srcs/begin.c \
				srcs/butler.c \
				srcs/dinner_cycle.c \
				srcs/dinner_utils.c \
				srcs/get_set.c \
				srcs/initialize.c \
				srcs/main.c \
				srcs/one_guest.c \
				srcs/printer.c \
				srcs/self_check.c \
				srcs/errors_clean.c \
				srcs/utils.c

OBJECT_FILES = $(SOURCE_FILES:.c=.o)

NAME = philo

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