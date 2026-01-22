/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:55:24 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 13:57:03 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collect_sprite(t_maze *m, t_player *p)
{
	int	tx;
	int	ty;
	int	i;

	tx = (int)(p->pos.x);
	ty = (int)(p->pos.y);
	if (m->map.grid[ty][tx] != 'C')
		return ;
	m->map.grid[ty][tx] = '0';
	i = 0;
	while (i < m->sprite_count)
	{
		if (m->sprites[i].active && (int)(m->sprites[i].pos.x) == tx
			&& (int)(m->sprites[i].pos.y) == ty)
		{
			m->sprites[i].active = 0;
			break ;
		}
		i++;
	}
}

//tex_x: the x-coordinate on the sprite texture 
//  corresponding to the current screen column
//d: a value used to calculate the y-coordinate on the sprite texture
//tex_y: the y-coordinate on the sprite texture
//  corresponding to the current screen row
//c: the color value fetched from the sprite texture at (tex_x, tex_y)

void	draw_sprite_column(t_maze *m, t_sprite_params *p, int x)
{
	int	tex_x;
	int	y;
	int	d;
	int	tex_y;
	int	c;

	tex_x = (int)(256 * (x - (-p->sw / 2 + p->ssx)) * m->sprite_frames.width
			/ p->sw) / 256;
	y = p->dsy;
	while (y <= p->dey)
	{
		d = (y - p->bob) * 256 - m->win_h * 128 + p->sh * 128;
		tex_y = ((d * m->sprite_frames.height) / p->sh) / 256;
		c = get_tex_pixel_safe(&m->sprite_frames, tex_x, tex_y);
		if ((c & 0x00FFFFFF) != 0)
			put_pixel(&m->img, x, y, c);
		y++;
	}
}

void	render_single_sprite(t_maze *m, t_sprite *s)
{
	t_sprite_params	p;
	int				x;

	init_sprite_render_params(s, m, &p);
	if (p.ty <= 0)
		return ;
	calculate_sprite_dimensions(&p, m);
	clamp_sprite_bounds(&p, m);
	x = p.dsx;
	while (x <= p.dex)
	{
		if (p.ty < m->zbuffer[x])
			draw_sprite_column(m, &p, x);
		x++;
	}
}

void	render_sprites(t_maze *m)
{
	int	i;

	if (!m || !m->sprite_count || !m->zbuffer)
		return ;
	compute_all_distances(m);
	sort_sprites(m);
	update_sprite_animation(m);
	i = 0;
	while (i < m->sprite_count)
	{
		if (m->sprites[i].active)
			render_single_sprite(m, &m->sprites[i]);
		i++;
	}
}
