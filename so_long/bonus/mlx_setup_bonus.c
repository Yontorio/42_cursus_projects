/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:42:29 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/07 23:21:30 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	open_door(t_data *data)
{
	t_pos	pos;
	void	*img;

	pos = find_position(data->map, 'E');
	pos.col *= SIZE;
	pos.row *= SIZE;
	img = data->img[EXIT_OPEN];
	mlx_put_image_to_window(data->mlx, data->win, img, pos.col, pos.row);
}

static int	key_event(int key, t_data *data)
{
	if (key == XK_Escape)
		close_window(data);
	else if (key == XK_Up)
		move(data, PLAYER_B, 0, -1);
	else if (key == XK_Right)
		move(data, PLAYER_R, 1, 0);
	else if (key == XK_Left)
		move(data, PLAYER_L, -1, 0);
	else if (key == XK_Down)
		move(data, PLAYER_F, 0, 1);
	if (data->collec_tot == 0)
		open_door(data);
	return (0);
}

static void	hooks_set_up(t_data *data)
{
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, key_event, data);
}

void	mlx_set_up(t_data *data, char **map)
{
	data->map = map;
	data->width = ft_strlen(data->map[0]) * SIZE;
	data->height = size_map(data->map) * SIZE;
	data->position = find_position(data->map, 'P');
	data->collec_tot = count_collec(data->map);
	data->moves_tot = -1;
	data->win = NULL;
	data->img[0] = NULL;
	data->enemy[0] = NULL;
	set_files(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_game(data, data->map, "Error\nMlx connection failed\n", 0);
	set_images(data);
	data->win = mlx_new_window(data->mlx, data->width, data->height,
			"./so_long");
	if (!data->win)
		exit_game(data, data->map, "Error\nMlx window failed\n", 0);
	display_images(data);
	mlx_set_font(data->mlx, data->win, "10x20");
	print_moves(data);
	mlx_loop_hook(data->mlx, enemy, data);
	hooks_set_up(data);
}
