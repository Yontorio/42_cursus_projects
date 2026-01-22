NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I includes -I /usr/include/minilibx-linux
MLX_FLAGS   = -L/usr/include/minilibx-linux -lmlx -lX11 -lXext -lm

HEADERS    = includes/cub3d.h \
             includes/librairies.h \
             includes/memtrack.h \
             includes/utils.h \
             includes/stdfcts.h

SRCS = sources/main.c \
       sources/maze/eternal_maze.c \
       sources/maze/maze_struct.c \
       sources/maze/maze_setup.c \
       sources/maze/load_textures.c \
       sources/maze/destroy_maze.c \
       sources/init/init_maze.c \
       sources/init/init_structs.c \
       sources/init/file_validity.c \
       sources/hooks/hooks.c \
       sources/hooks/hooks1.c \
       sources/hooks/hooks2.c \
       sources/parser/config_parser.c \
       sources/parser/map_validity.c \
       sources/parser/map_extractor.c \
       sources/parser/env_extractor.c \
       sources/parser/rgb_resolution.c \
       sources/parser/player.c \
       sources/errors/error.c \
       sources/render/render.c \
       sources/render/minimap.c \
       sources/render/minimap_utils.c \
       sources/render/minimap_draw.c \
       sources/render/minimap_effects.c \
       sources/render/rays.c \
       sources/render/sprites.c \
       sources/render/sprite_utils.c \
       sources/render/sprite_distance.c \
       sources/render/sprite_render.c \
       sources/render/rays_utils2.c \
       sources/render/rays_utils.c \
       memtrack/smalloc.c \
       memtrack/clear_data.c \
       memtrack/destroy_all.c \
       memtrack/find_sections.c \
       memtrack/add_allocation.c \
       memtrack/new_allocation.c \
       memtrack/create_section.c \
       memtrack/current_section.c \
       memtrack/destroy_section.c \
       memtrack/free_one_pointer.c \
       memtrack/safe_open.c \
       utils/read_file.c \
       utils/count_char.c \
       utils/skip_spaces.c \
       utils/split_lines.c \
       utils/split_one_time.c \
       utils/check_if_match.c \
       utils/join_two_strings.c \
       stdfcts/ft_min.c \
       stdfcts/ft_abs.c \
       stdfcts/ft_itoa.c \
       stdfcts/ft_atoi.c \
       stdfcts/ft_split.c \
       stdfcts/ft_numlen.c \
       stdfcts/ft_substr.c \
       stdfcts/ft_strcmp.c \
       stdfcts/ft_strchr.c \
       stdfcts/ft_memset.c \
       stdfcts/ft_memcpy.c \
       stdfcts/ft_strcat.c \
       stdfcts/ft_strlen.c \
       stdfcts/ft_strrchr.c \
       stdfcts/ft_isspace.c \
       stdfcts/ft_strjoin.c \
       stdfcts/ft_isalnum.c \
       stdfcts/ft_isalpha.c \
       stdfcts/ft_strndup.c \
       stdfcts/ft_strncmp.c \
       stdfcts/ft_isdigit.c \
       stdfcts/ft_realloc.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re