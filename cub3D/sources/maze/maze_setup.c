/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:54:56 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 13:39:07 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	maze_setup(void)
{
	t_maze	*maze;

	maze = *maze_struct();
	maze->mlx = mlx_init();
	if (!maze->mlx)
		error_exit("MLX initialization failed");
	load_textures(maze);
	load_sprite_frames(maze);
	init_sprites(maze);
	maze->win = mlx_new_window(maze->mlx, maze->win_w, maze->win_h,
			"ETERNAL MAZE");
	if (!maze->win)
		error_exit("window creation failed");
	maze->img.img = mlx_new_image(maze->mlx, maze->win_w, maze->win_h);
	if (!maze->img.img)
		error_exit("image creation failed");
	maze->img.addr = mlx_get_data_addr(maze->img.img, &maze->img.bpp,
			&maze->img.line_len, &maze->img.endian);
	return (true);
}
