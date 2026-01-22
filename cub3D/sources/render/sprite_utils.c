/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:55:29 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 13:58:37 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_sprite_frames(t_maze *m)
{
	if (!m || !m->mlx)
		return ;
	m->sprite_frame_count = SPRITE_FRAME_COUNT;
	m->sprite_frames = m->tex[5];
}

static void	init_sprite_positions(t_maze *m, int *i, int y, int x)
{
	while (m->map.grid[y][x])
	{
		if (m->map.grid[y][x] == 'C')
		{
			m->sprites[*i].pos.x = x + 0.5;
			m->sprites[*i].pos.y = y + 0.5;
			m->sprites[*i].active = 1;
			m->sprites[*i].frame = 0;
			m->sprites[*i].dist = 0;
			(*i)++;
		}
		x++;
	}
}

static void	count_and_allocate_sprites(t_maze *m, int *count)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->map.height)
	{
		x = 0;
		while (m->map.grid[y][x])
			if (m->map.grid[y][x++] == 'C')
				(*count)++;
		y++;
	}
	m->sprite_count = *count;
	if (*count)
		m->sprites = allocate_memory(sizeof(t_sprite) * (*count));
}

void	init_sprites(t_maze *m)
{
	int	count;
	int	i;
	int	y;
	int	x;

	if (!m)
		return ;
	count = 0;
	count_and_allocate_sprites(m, &count);
	if (!count)
		return ;
	i = 0;
	y = 0;
	while (y < m->map.height)
	{
		x = 0;
		init_sprite_positions(m, &i, y, x);
		y++;
	}
}
