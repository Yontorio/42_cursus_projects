COMPILER = cc

COMPILER_FLAGS = -Wall -Wextra -Werror

SOURCE_FILES =    push.c \
                  sort.c \
                  swap.c \
                  rotate.c \
                  execute.c \
                  ft_atol.c \
                  ft_split.c \
                  ft_strlen.c \
                  is_sorted.c \
                  fill_infos.c \
                  start_sort.c \
                  rev_rotate.c \
                  main_helper.c \
                  final_moves.c \
                  find_familly.c \
                  get_position.c \
                  lst_operation.c \
                  check_element.c

BONUS_FILES =     checks_bonus.c \
                  ft_strncmp.c \
                  get_next_line.c \
                  get_next_line_utils.c

OBJECT_FILES = $(SOURCE_FILES:.c=.o)
BONUS_OBJECTS = $(BONUS_FILES:.c=.o)

NAME = push_swap

BONUS = checker

RM = rm -f

HEADER_FILES = push_swap.h

BONUS_HEADERS = checker_bonus.h

%.o: %.c
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

$(NAME): $(OBJECT_FILES) $(HEADER_FILES)
	$(COMPILER) $(COMPILER_FLAGS) push_swap.c $(OBJECT_FILES) -o $(NAME)

$(BONUS): $(BONUS_OBJECTS) $(BONUS_HEADERS) $(OBJECT_FILES)
	$(COMPILER) $(COMPILER_FLAGS) checker_bonus.c $(BONUS_OBJECTS) $(OBJECT_FILES) -o $(BONUS)

bonus: $(BONUS)

all: $(NAME)

clean:
	$(RM) $(OBJECT_FILES) $(BONUS_OBJECTS) 

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus