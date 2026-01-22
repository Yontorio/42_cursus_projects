/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:15:11 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 16:35:25 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		square(int x);
int		inside_circle(t_mm mm, int x, int y);
void	put_pixel(t_img *img, int x, int y, int color);

void	draw_player(t_img *img, t_mm mm)
{
	int	x;
	int	y;

	y = -MM_PLAYER_RADIUS;
	while (y <= MM_PLAYER_RADIUS)
	{
		x = -MM_PLAYER_RADIUS;
		while (x <= MM_PLAYER_RADIUS)
		{
			if (square(x) + square(y) <= square(MM_PLAYER_RADIUS))
				put_pixel(img, mm.cx + x, mm.cy + y, MM_PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_square_clipped(t_img *img, t_mm mm, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MM_TILE)
	{
		x = 0;
		while (x < MM_TILE)
		{
			if (inside_circle(mm, mm.sx + x, mm.sy + y))
				put_pixel(img, mm.sx + x, mm.sy + y, color);
			x++;
		}
		y++;
	}
}

void	draw_fov(t_player *p, t_img *img, t_mm mm)
{
	double	lx;
	double	ly;
	double	rx;
	double	ry;
	int		i;

	i = 0;
	lx = p->dir.x - p->plane.x;
	ly = p->dir.y - p->plane.y;
	rx = p->dir.x + p->plane.x;
	ry = p->dir.y + p->plane.y;
	while (i < mm.radius)
	{
		if (inside_circle(mm, mm.cx + lx * i, mm.cy + ly * i))
			put_pixel(img, mm.cx + lx * i, mm.cy + ly * i, MM_PLAYER_COLOR);
		if (inside_circle(mm, mm.cx + rx * i, mm.cy + ry * i))
			put_pixel(img, mm.cx + rx * i, mm.cy + ry * i, MM_PLAYER_COLOR);
		i++;
	}
}

static void	draw_coin_clipped(t_img *img, t_mm mm)
{
	int	x;
	int	y;
	int	r;
	int	cx;
	int	cy;

	cx = mm.sx + MM_TILE / 4;
	cy = mm.sy + MM_TILE / 4;
	r = MM_TILE / 4;
	y = cy - r;
	while (y <= cy + r)
	{
		x = cx - r;
		while (x <= cx + r)
		{
			if (square(x - cx) + square(y - cy) <= square(r))
				if (inside_circle(mm, x, y))
					put_pixel(img, x, y, 0xEAB543);
			x++;
		}
		y++;
	}
}

void	pick_color(t_maze *maze, t_mm mm, char c)
{
	if (c == '1')
		draw_square_clipped(&maze->img, mm, 0x111111);
	else if (c == '0')
		draw_square_clipped(&maze->img, mm, 0x888888);
	else if (c == 'D')
		draw_square_clipped(&maze->img, mm, 0x613900);
	else if (c == 'd')
		draw_square_clipped(&maze->img, mm, 0x555555);
	else if (c == 'C')
	{
		draw_square_clipped(&maze->img, mm, 0x888888);
		draw_coin_clipped(&maze->img, mm);
	}
}
