/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eternal_maze.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:01:51 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 18:02:29 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	eternal_maze(void)
{
	t_maze	*maze;

	maze = *maze_struct();
	mlx_loop_hook(maze->mlx, render_maze, maze);
	mlx_hook(maze->win, 6, 1L << 6, mouse_rotate, maze);
	mlx_hook(maze->win, 2, 1L << 0, key_press, maze);
	mlx_hook(maze->win, 3, 1L << 1, key_release, maze);
	mlx_hook(maze->win, 17, 0, close_window, maze);
	mlx_loop(maze->mlx);
	return (0);
}
