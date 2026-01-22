/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_maze.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:25:11 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/12 15:52:35 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	init_maze(t_maze **pointer)
{
	t_maze	*maze;

	*pointer = allocate_memory(sizeof(t_maze));
	maze = *pointer;
	maze->mlx = NULL;
	maze->win = NULL;
	maze->win_h = HEIGHT;
	maze->win_w = WIDTH;
	maze->mouse_x = (int)WIDTH / 2;
	maze->zbuffer = allocate_memory(sizeof(double) * maze->win_w);
	maze->sprite_count = 0;
	maze->sprites = NULL;
	maze->sprite_frame_count = 0;
	maze->frame_tick = 0;
	init_img(&maze->img);
	init_env(&maze->env);
	init_map(&maze->map);
	ft_memset(&maze->keys, 0, sizeof(t_keys));
	ft_memset(&maze->tex, 0, sizeof(t_img) * 6);
	return (true);
}
