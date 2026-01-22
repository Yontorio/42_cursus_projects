COMPILER = cc

COMPILER_FLAGS = -Wall -Wextra -Werror 

LIBS = -L/usr/include/minilibx-linux -lmlx -lXext -lX11

SOURCE_FILES = 	mandatory/so_long.c mandatory/mlx_exit.c mandatory/mlx_img.c\
				mandatory/mlx_setup.c mandatory/parsing.c mandatory/mlx_moves.c\
				mandatory/file_check.c mandatory/flood.c mandatory/map_check.c mandatory/map_utils.c\

BONUS_FILES = 	bonus/so_long_bonus.c bonus/mlx_exit_bonus.c bonus/mlx_img_bonus.c\
				bonus/file_check_bonus.c bonus/flood_bonus.c bonus/map_check_bonus.c bonus/map_utils_bonus.c\
				bonus/mlx_setup_bonus.c bonus/mlx_anime_bonus.c bonus/parsing_bonus.c bonus/mlx_moves_bonus.c\

MANDATORY_OBJECTS = $(SOURCE_FILES:.c=.o)

BONUS_OBJECTS = $(BONUS_FILES:.c=.o)

NAME = so_long

NAME_1 = so_long_bonus

LIB_DIR = libft

LIBFT = libft/libft.a

RM = rm -f

all: $(NAME)

%.o: %.c 
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

$(NAME): $(MANDATORY_OBJECTS) $(LIBFT)
	$(COMPILER) $(COMPILER_FLAGS) $(MANDATORY_OBJECTS) $(LIBFT) $(LIBS) -o $(NAME)

$(NAME_1): $(BONUS_OBJECTS) $(LIBFT)
	$(COMPILER) $(COMPILER_FLAGS) $(BONUS_OBJECTS) $(LIBFT) $(LIBS) -o $(NAME_1)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

bonus: $(NAME_1)

clean:
	$(RM) $(MANDATORY_OBJECTS) $(BONUS_OBJECTS)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	$(RM) $(NAME) $(NAME_1)

re: fclean all

.PHONY: all clean fclean re bonus
