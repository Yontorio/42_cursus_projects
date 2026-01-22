/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:12:52 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/12 11:40:31 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_line_height(t_maze *m, double dist, t_line *line)
{
	line->height = (int)(m->win_h / dist);
	line->start = m->win_h / 2 - line->height / 2;
	line->end = line->start + line->height;
	if (line->start < 0)
		line->start = 0;
	if (line->end >= m->win_h)
		line->end = m->win_h - 1;
}

int	get_tex_id(t_vec *ray, t_dda dda)
{
	if (dda.tile == 'D')
	{
		return (DOOR);
	}
	else if (dda.tile == '1')
	{
		if (dda.side == 0 && ray->x > 0)
			return (EAST);
		else if (dda.side == 0 && ray->x < 0)
			return (WEST);
		else if (dda.side == 1 && ray->y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
	return (0);
}

double	get_wall_x(t_player *p, t_vec *ray, int side, double dist)
{
	double	wall_x;

	if (side == 0)
		wall_x = p->pos.y + dist * ray->y;
	else
		wall_x = p->pos.x + dist * ray->x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	draw_textured_line(t_maze *m, int x, t_line *line, t_tex_info *tex)
{
	double	tex_pos;
	double	step;
	int		y;
	int		color;

	step = (double)tex->img->height / line->height;
	tex_pos = (line->start - m->win_h / 2 + line->height / 2) * step;
	y = line->start;
	while (y <= line->end)
	{
		tex->y = ((int)tex_pos % tex->img->height + tex->img->height)
			% tex->img->height;
		tex_pos += step;
		color = get_tex_pixel_safe(tex->img, tex->x, tex->y);
		put_pixel(&m->img, x, y, color);
		y++;
	}
}

void	raycasting(t_maze *m)
{
	int			x;
	t_vec		ray;
	t_dda		dda;
	t_line		line;
	t_tex_info	tex;

	x = 0;
	while (x < m->win_w)
	{
		init_ray(m, x, &ray);
		init_dda(&m->map.player, &ray, &dda);
		perform_dda(m, &dda);
		line.dist = calc_distance(&dda);
		calc_line_height(m, line.dist, &line);
		tex.img = &m->tex[get_tex_id(&ray, dda)];
		tex.wall_x = get_wall_x(&m->map.player, &ray, dda.side, line.dist);
		tex.x = (int)(tex.wall_x * tex.img->width);
		if ((dda.side == 0 && ray.x > 0) || (dda.side == 1 && ray.y < 0))
			tex.x = tex.img->width - tex.x - 1;
		draw_textured_line(m, x, &line, &tex);
		if (m->zbuffer)
			m->zbuffer[x] = line.dist;
		x++;
	}
	render_sprites(m);
}
