/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:58:31 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 14:00:46 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_maze *m, double y, double x)
{
	int	ty;
	int	tx;

	ty = (int)(y - 0.2);
	while (ty <= (int)(y + 0.2))
	{
		tx = (int)(x - 0.2);
		while (tx <= (int)(x + 0.2))
		{
			if (m->map.grid[ty][tx] == '1' || m->map.grid[ty][tx] == 'D'
				|| m->map.grid[ty][tx] == '2')
				return (1);
			tx++;
		}
		ty++;
	}
	collect_sprite(m, &m->map.player);
	return (0);
}

void	move_forward(t_maze *m, t_player *p)
{
	double	next_x;
	double	next_y;

	next_x = p->pos.x + p->dir.x * MOVE_SPEED;
	next_y = p->pos.y + p->dir.y * MOVE_SPEED;
	if (!is_wall(m, p->pos.y, next_x))
		p->pos.x = next_x;
	if (!is_wall(m, next_y, p->pos.x))
		p->pos.y = next_y;
}

void	move_backward(t_maze *m, t_player *p)
{
	double	next_x;
	double	next_y;

	next_x = p->pos.x - p->dir.x * MOVE_SPEED;
	next_y = p->pos.y - p->dir.y * MOVE_SPEED;
	if (!is_wall(m, p->pos.y, next_x))
		p->pos.x = next_x;
	if (!is_wall(m, next_y, p->pos.x))
		p->pos.y = next_y;
}

void	move_left(t_maze *m, t_player *p)
{
	double	px;
	double	py;
	double	next_x;
	double	next_y;

	px = p->dir.y;
	py = -p->dir.x;
	next_x = p->pos.x + px * MOVE_SPEED;
	next_y = p->pos.y + py * MOVE_SPEED;
	if (!is_wall(m, p->pos.y, next_x))
		p->pos.x = next_x;
	if (!is_wall(m, next_y, p->pos.x))
		p->pos.y = next_y;
}

void	move_right(t_maze *m, t_player *p)
{
	double	px;
	double	py;
	double	next_x;
	double	next_y;

	px = -p->dir.y;
	py = p->dir.x;
	next_x = p->pos.x + px * MOVE_SPEED;
	next_y = p->pos.y + py * MOVE_SPEED;
	if (!is_wall(m, p->pos.y, next_x))
		p->pos.x = next_x;
	if (!is_wall(m, next_y, p->pos.x))
		p->pos.y = next_y;
}
