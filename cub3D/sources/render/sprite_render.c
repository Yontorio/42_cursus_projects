/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:55:24 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/12 12:58:27 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_sprite_animation(t_maze *m)
{
	if (!m)
		return ;
	m->frame_tick = (m->frame_tick + 1) % 60;
}

/*this function converts the sprite's position from World Space
(absolute map coordinates) to Camera Space (relative to the player's view).
we need this fct to calculate the depth and the camerax*/

void	init_sprite_render_params(t_sprite *s, t_maze *m,
			t_sprite_params *p)
{
	double	sx;
	double	sy;

	sx = s->pos.x - m->map.player.pos.x;
	sy = s->pos.y - m->map.player.pos.y;
	p->inv = 1.0 / (m->map.player.plane.x * m->map.player.dir.y
			- m->map.player.dir.x * m->map.player.plane.y);
	p->tx = p->inv * (m->map.player.dir.y * sx - m->map.player.dir.x * sy);
	p->ty = p->inv * (-m->map.player.plane.y * sx
			+ m->map.player.plane.x * sy);
}

//p->ssx is center of the sprite on screen
//p->sh is height of the sprite
//p->sw is width of the sprite
//p->bob is vertical offset for bobbing effect
//p->dsy and p->dey are the start and end y-coordinates 
//  starting from the center of the screen
//p->dsx and p->dex are the start and end 
//  x-coordinates of the sprite on screen

void	calculate_sprite_dimensions(t_sprite_params *p, t_maze *m)
{
	p->ssx = (int)((m->win_w / 2) * (1 + p->tx / p->ty));
	p->sh = abs((int)(m->win_h / (p->ty * 1.2)));
	p->sw = p->sh;
	p->bob = (int)(5 * sin(m->frame_tick / 60.0 * 2 * M_PI));
	p->dsy = -p->sh / 2 + m->win_h / 2 + p->bob;
	p->dey = p->sh / 2 + m->win_h / 2 + p->bob;
	p->dsx = -p->sw / 2 + p->ssx;
	p->dex = p->sw / 2 + p->ssx;
}

void	clamp_sprite_bounds(t_sprite_params *p, t_maze *m)
{
	if (p->dsy < 0)
	{
		p->dsy = 0;
	}
	if (p->dey >= m->win_h)
	{
		p->dey = m->win_h - 1;
	}
	if (p->dsx < 0)
	{
		p->dsx = 0;
	}
	if (p->dex >= m->win_w)
	{
		p->dex = m->win_w - 1;
	}
}
