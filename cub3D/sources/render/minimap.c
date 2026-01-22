/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:01:09 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 16:18:06 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_rounded_map(t_maze *maze, t_mm mm)
{
	int	x;
	int	y;

	y = 0;
	while (y < maze->map.height)
	{
		x = 0;
		while (x < maze->map.width)
		{
			mm.sx = mm.cx + (x - maze->map.player.pos.x) * MM_TILE;
			mm.sy = mm.cy + (y - maze->map.player.pos.y) * MM_TILE;
			if (inside_circle(mm, mm.sx, mm.sy))
				pick_color(maze, mm, maze->map.grid[y][x]);
			x++;
		}
		y++;
	}
}

static t_mm	set_minimap_struct(void)
{
	t_mm	minimap;

	minimap.cx = MM_PADDING + MM_RADIUS;
	minimap.cy = MM_PADDING + MM_RADIUS;
	minimap.radius = MM_RADIUS;
	minimap.sx = 0;
	minimap.sy = 0;
	return (minimap);
}

void	render_minimap(t_maze *maze)
{
	t_mm		minimap;
	t_player	*player;
	t_img		*img;

	img = &maze->img;
	player = &maze->map.player;
	minimap = set_minimap_struct();
	for_each_circle_pixel(img, minimap, bg_pixel_cb);
	draw_rounded_map(maze, minimap);
	draw_player(img, minimap);
	draw_fov(player, img, minimap);
	minimap.radius += 10;
	for_each_circle_pixel(img, minimap, border_pixel_cb);
}
