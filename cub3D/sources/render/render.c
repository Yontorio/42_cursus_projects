/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:52:07 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 17:52:45 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_maze *m)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < m->win_h)
	{
		if (y < m->win_h / 2)
			color = m->env.ceiling;
		else
			color = m->env.floor;
		x = 0;
		while (x < m->win_w)
		{
			put_pixel(&m->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap_compass(t_maze *m)
{
	mlx_string_put(m->mlx, m->win, MM_PADDING + MM_RADIUS - 4, MM_PADDING + 5,
		MM_TEXT_COLOR, "N");
	mlx_string_put(m->mlx, m->win, MM_PADDING + MM_RADIUS - 3, MM_PADDING + 6
		+ MM_RADIUS * 2, MM_TEXT_COLOR, "S");
	mlx_string_put(m->mlx, m->win, MM_PADDING - 4, MM_PADDING + MM_RADIUS + 2,
		MM_TEXT_COLOR, "W");
	mlx_string_put(m->mlx, m->win, MM_PADDING - 3 + MM_RADIUS * 2, MM_PADDING
		+ MM_RADIUS + 3, MM_TEXT_COLOR, "E");
}

int	render_frame(t_maze *maze)
{
	draw_floor_ceiling(maze);
	raycasting(maze);
	render_minimap(maze);
	mlx_put_image_to_window(maze->mlx, maze->win, maze->img.img, 0, 0);
	draw_minimap_compass(maze);
	return (0);
}
