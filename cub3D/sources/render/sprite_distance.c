/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:55:27 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 16:59:14 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_all_distances(t_maze *m)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < m->sprite_count)
	{
		dx = m->sprites[i].pos.x - m->map.player.pos.x;
		dy = m->sprites[i].pos.y - m->map.player.pos.y;
		m->sprites[i].dist = dx * dx + dy * dy;
		i++;
	}
}

void	sort_sprites(t_maze *m)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < m->sprite_count - 1)
	{
		j = i + 1;
		while (j < m->sprite_count)
		{
			if (m->sprites[i].dist < m->sprites[j].dist)
			{
				tmp = m->sprites[i];
				m->sprites[i] = m->sprites[j];
				m->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
