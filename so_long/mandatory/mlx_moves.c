/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:16:03 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/03 19:23:54 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_moves(t_data *data)
{
	data->moves_tot++;
	ft_putstr_fd("\r", 1);
	ft_putstr_fd("moves : ", 1);
	ft_putnbr_fd(data->moves_tot, 1);
}

static void	complet_move(t_data *data, int direct, int nx, int ny)
{
	int		x_p;
	int		y_p;
	char	c;
	void	*img[2];

	y_p = data->position.row;
	x_p = data->position.col;
	c = data->map[y_p + ny][x_p + nx];
	if (c == 'C')
		data->collec_tot--;
	img[0] = data->img[FLOOR];
	img[1] = data->img[direct];
	data->map[y_p][x_p] = '0';
	data->map[y_p + ny][x_p + nx] = 'P';
	data->position.col += nx;
	data->position.row += ny;
	x_p *= SIZE;
	y_p *= SIZE;
	mlx_put_image_to_window(data->mlx, data->win, img[0], x_p, y_p);
	x_p += nx * SIZE;
	y_p += ny * SIZE;
	mlx_put_image_to_window(data->mlx, data->win, img[1], x_p, y_p);
	print_moves(data);
}

static void	move_to_door(t_data *data, int direct, int nx, int ny)
{
	int		x_p;
	int		y_p;
	void	*img[2];

	y_p = data->position.row;
	x_p = data->position.col;
	img[0] = data->img[FLOOR];
	img[1] = data->img[PLAYER_R_E + direct];
	data->map[y_p][x_p] = '0';
	data->position.col += nx;
	data->position.row += ny;
	x_p *= SIZE;
	y_p *= SIZE;
	mlx_put_image_to_window(data->mlx, data->win, img[0], x_p, y_p);
	x_p += nx * SIZE;
	y_p += ny * SIZE;
	mlx_put_image_to_window(data->mlx, data->win, img[1], x_p, y_p);
	print_moves(data);
}

static void	move_on_door(t_data *data, int direct, int nx, int ny)
{
	char	collec;
	int		x_p;
	int		y_p;
	void	*img[2];

	y_p = data->position.row;
	x_p = data->position.col;
	collec = data->map[y_p + ny][x_p + nx];
	if (collec == 'C')
		data->collec_tot--;
	img[0] = data->img[EXIT_CLOSE];
	img[1] = data->img[direct];
	data->map[y_p + ny][x_p + nx] = 'P';
	data->position.col += nx;
	data->position.row += ny;
	x_p *= SIZE;
	y_p *= SIZE;
	mlx_put_image_to_window(data->mlx, data->win, img[0], x_p, y_p);
	x_p += nx * SIZE;
	y_p += ny * SIZE;
	mlx_put_image_to_window(data->mlx, data->win, img[1], x_p, y_p);
	print_moves(data);
}

void	move(t_data *data, int direct, int nx, int ny)
{
	int		x_p;
	int		y_p;
	char	c;

	y_p = data->position.row;
	x_p = data->position.col;
	c = data->map[y_p + ny][x_p + nx];
	if (c != '1' && c != 'E' && data->map[y_p][x_p] != 'E')
		complet_move(data, direct, nx, ny);
	else if (c == 'E' && data->collec_tot == 0)
		exit_game(data, data->map, NULL, WIN);
	else if (c == 'E')
		move_to_door(data, direct, nx, ny);
	else if (c != '1' && data->map[y_p][x_p] == 'E')
		move_on_door(data, direct, nx, ny);
}
