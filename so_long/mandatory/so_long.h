/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:16:56 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/06 00:41:52 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define WIN 1
# define SIZE 70
# define IMAGES 14

typedef struct s_pos
{
	int		row;
	int		col;
}			t_pos;

typedef struct s_state
{
	int		collectible;
	int		position;
	int		exit;
}			t_state;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img[IMAGES];
	char	*files[IMAGES];
	char	**map;
	int		collec_tot;
	int		moves_tot;
	int		width;
	int		height;
	t_pos	position;
}			t_data;

enum		e_texture
{
	PLAYER_R = 0,
	PLAYER_L,
	PLAYER_F,
	PLAYER_B,
	PLAYER_R_E,
	PLAYER_L_E,
	PLAYER_F_E,
	PLAYER_B_E,
	FLOOR,
	WALL,
	COLLEC,
	EXIT_OPEN,
	EXIT_CLOSE
};

int			newlines_check(char *str);
int			count_char(char *s, char c);
int			size_map(char **map);
void		free_map(char **map);
void		map_check(char **map);
int			check_map_valide(char **map);
int			file_name_check(char *name);
char		**parse_map(char *name);
void		exit_error(char **map, char *msg);
int			count_collec(char **map);
t_pos		find_position(char **map, char c);
void		mlx_set_up(char **map);
void		exit_game(t_data *data, char **map, char *msg, int type);
int			close_window(t_data *data);
void		move(t_data *data, int direct, int nx, int ny);
void		print_moves(t_data *data);
int			display_images(t_data *data);
void		clean(t_data *data, int code);
void		set_files(t_data *data);
void		set_images(t_data *data);

#endif
