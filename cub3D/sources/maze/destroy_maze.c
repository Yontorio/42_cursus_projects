/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_maze.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:01:42 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 18:43:11 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_maze(void)
{
	int		i;
	t_maze	*maze;

	maze = *maze_struct();
	if (!maze)
		return ;
	if (maze->mlx)
	{
		if (maze->img.img)
			mlx_destroy_image(maze->mlx, maze->img.img);
		i = 0;
		while (i < 6)
		{
			if (maze->tex[i].img)
				mlx_destroy_image(maze->mlx, maze->tex[i].img);
			i++;
		}
		if (maze->win)
			mlx_destroy_window(maze->mlx, maze->win);
		mlx_destroy_display(maze->mlx);
		free(maze->mlx);
	}
}
