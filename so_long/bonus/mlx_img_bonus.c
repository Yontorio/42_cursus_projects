/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:21:27 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/07 22:30:56 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_files(t_data *data)
{
	data->files[PLAYER_R] = "textures/r.xpm";
	data->files[PLAYER_L] = "textures/l.xpm";
	data->files[PLAYER_F] = "textures/f.xpm";
	data->files[PLAYER_B] = "textures/b.xpm";
	data->files[PLAYER_R_E] = "textures/ddr.xpm";
	data->files[PLAYER_L_E] = "textures/dl.xpm";
	data->files[PLAYER_F_E] = "textures/ddf.xpm";
	data->files[PLAYER_B_E] = "textures/ddb.xpm";
	data->files[FLOOR] = "textures/Ice.xpm";
	data->files[WALL] = "textures/wall4.xpm";
	data->files[COLLEC] = "textures/c.xpm";
	data->files[EXIT_OPEN] = "textures/do.xpm";
	data->files[EXIT_CLOSE] = "textures/dc.xpm";
	data->files[ENEMY_F1] = "textures/en1.xpm";
	data->files[ENEMY_F2] = "textures/en3.xpm";
	data->files[ENEMY_F3] = "textures/en4.xpm";
	data->files[ENEMY_F4] = "textures/en5.xpm";
	data->files[ENEMY_F5] = "textures/en8.xpm";
	data->files[ENEMY_F6] = "textures/en7.xpm";
	data->files[ENEMY_F7] = "textures/en6.xpm";
	data->files[ENEMY_F8] = "textures/en2.xpm";
}

static void	set_enemy(t_data *data, int i)
{
	int	j;
	int	x;
	int	y;

	j = 0;
	while (i < ENEMY)
		data->enemy[j++] = NULL;
	j = 0;
	while (i < IMAGES + ENEMY)
	{
		data->enemy[j] = mlx_xpm_file_to_image(data->mlx, data->files[i], &x,
				&y);
		if (data->enemy[j] == NULL || x != SIZE || y != SIZE)
			clean(data, 1);
		i++;
		j++;
	}
	data->enemy[j] = NULL;
}

void	set_images(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < IMAGES)
		data->img[i++] = NULL;
	i = 0;
	while (i < IMAGES)
	{
		data->img[i] = mlx_xpm_file_to_image(data->mlx, data->files[i], &x, &y);
		if (data->img[i] == NULL || x != SIZE || y != SIZE)
			clean(data, 1);
		i++;
	}
	data->img[i] = NULL;
	set_enemy(data, i);
}

static void	put_image(t_data *data, int w, int j, int i)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img[w], j * SIZE, i
		* SIZE);
}

void	display_images(t_data *data)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'P')
				put_image(data, PLAYER_F, j, i);
			else if (data->map[i][j] == '1')
				put_image(data, WALL, j, i);
			else if (data->map[i][j] == '0')
				put_image(data, FLOOR, j, i);
			else if (data->map[i][j] == 'C')
				put_image(data, COLLEC, j, i);
			else if (data->map[i][j] == 'E')
				put_image(data, EXIT_CLOSE, j, i);
			else if (data->map[i][j] == 'V')
				put_image(data, FLOOR, j, i);
			j++;
		}
		i++;
	}
}
