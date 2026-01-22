/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:58:31 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 13:25:18 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	p->dir.x = p->dir.x * cos(angle) - p->dir.y * sin(angle);
	p->dir.y = old_dir_x * sin(angle) + p->dir.y * cos(angle);
	p->plane.x = p->plane.x * cos(angle) - p->plane.y * sin(angle);
	p->plane.y = old_plane_x * sin(angle) + p->plane.y * cos(angle);
}

int	player_in_tile(t_player p, int tx, int ty)
{
	int	px;
	int	py;

	px = (int)p.pos.x;
	py = (int)p.pos.y;
	return (px == tx && py == ty);
}

void	try_open_door(t_maze *m)
{
	t_player	p;
	int			tx;
	int			ty;

	p = m->map.player;
	tx = (int)(p.pos.x + p.dir.x);
	ty = (int)(p.pos.y + p.dir.y);
	if (m->map.grid[ty][tx] == 'D')
	{
		m->map.grid[ty][tx] = 'd';
	}
	else if (m->map.grid[ty][tx] == 'd')
	{
		if (!player_in_tile(p, tx, ty))
			m->map.grid[ty][tx] = 'D';
	}
}

int	mouse_rotate(int x, int y, t_maze *maze)
{
	int	dx;

	(void)y;
	dx = x - maze->mouse_x;
	maze->mouse_x = x;
	rotate(&maze->map.player, dx * MOUSE_SENSOR);
	return (0);
}

int	close_window(void)
{
	destroy_maze();
	destroy_everything();
	exit(EXIT_SUCCESS);
	return (0);
}
