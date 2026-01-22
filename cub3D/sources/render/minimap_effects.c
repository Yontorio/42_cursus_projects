/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_effects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:01:09 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 16:58:50 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	soft_blur(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (r + 40) / 3;
	g = (g + 40) / 3;
	b = (b + 40) / 3;
	return ((r << 16) | (g << 8) | b);
}

void	for_each_circle_pixel(t_img *img, t_mm mm,
							void (*cb)(t_img *, t_mm, t_vec, int))
{
	t_vec	axe;
	int		dist_sq;

	axe.y = -mm.radius;
	while (axe.y <= mm.radius)
	{
		axe.x = -mm.radius;
		while (axe.x <= mm.radius)
		{
			dist_sq = square(axe.x) + square(axe.y);
			if (dist_sq <= square(mm.radius))
				cb(img, mm, axe, dist_sq);
			axe.x++;
		}
		axe.y++;
	}
}

void	bg_pixel_cb(t_img *img, t_mm mm, t_vec axe, int dist_sq)
{
	int	inner_sq;
	int	sx;
	int	sy;
	int	color;

	inner_sq = square(mm.radius - MM_BR_THICK);
	if (!(dist_sq >= inner_sq))
	{
		sx = mm.cx + axe.x;
		sy = mm.cy + axe.y ;
		color = get_pixel(img, sx, sy);
		put_pixel(img, sx, sy, soft_blur(color));
	}
}

void	border_pixel_cb(t_img *img, t_mm mm, t_vec axe, int dist_sq)
{
	int	sx;
	int	sy;
	int	base_r;
	int	base_inner_sq;
	int	inner_sq;

	sx = mm.cx + axe.x;
	sy = mm.cy + axe.y;
	base_r = mm.radius - MM_BR_THICK;
	base_inner_sq = square(base_r - 10);
	inner_sq = square(base_r);
	if (dist_sq >= inner_sq)
		put_pixel(img, sx, sy, MM_BR_COLOR);
	else if (dist_sq >= base_inner_sq)
		put_pixel(img, sx, sy, MM_BG_COLOR);
}
