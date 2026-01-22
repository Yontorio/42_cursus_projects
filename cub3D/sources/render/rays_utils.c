/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:12:52 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 17:50:35 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_pixel_safe(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}

void	init_ray(t_maze *m, int x, t_vec *ray)
{
	double	cam_x;

	cam_x = 2.0 * x / (double)m->win_w - 1.0;
	*ray = v_add(m->map.player.dir, v_scale(m->map.player.plane, cam_x));
}

void	init_dda(t_player *p, t_vec *ray, t_dda *d)
{
	d->map_x = (int)p->pos.x;
	d->map_y = (int)p->pos.y;
	d->delta_x = fabs(1 / ray->x);
	d->delta_y = fabs(1 / ray->y);
	if (ray->x < 0)
		d->step_x = -1;
	else
		d->step_x = 1;
	if (ray->x < 0)
		d->side_x = (p->pos.x - d->map_x) * d->delta_x;
	else
		d->side_x = (d->map_x + 1.0 - p->pos.x) * d->delta_x;
	if (ray->y < 0)
		d->step_y = -1;
	else
		d->step_y = 1;
	if (ray->y < 0)
		d->side_y = (p->pos.y - d->map_y) * d->delta_y;
	else
		d->side_y = (d->map_y + 1.0 - p->pos.y) * d->delta_y;
	d->tile = '\0';
}

void	perform_dda(t_maze *m, t_dda *d)
{
	while (1)
	{
		if (d->side_x < d->side_y)
		{
			d->side_x += d->delta_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_y += d->delta_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (m->map.grid[d->map_y][d->map_x] == '1'
			|| m->map.grid[d->map_y][d->map_x] == 'D')
		{
			d->tile = m->map.grid[d->map_y][d->map_x];
			break ;
		}
	}
}

double	calc_distance(t_dda *d)
{
	double	dist;

	if (d->side == 0)
		dist = d->side_x - d->delta_x;
	else
		dist = d->side_y - d->delta_y;
	return (dist);
}
