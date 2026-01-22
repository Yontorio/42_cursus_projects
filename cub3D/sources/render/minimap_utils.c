/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:01:09 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 16:58:29 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	square(int x)
{
	return (x * x);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*px;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	px = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)px = color;
}

int	get_pixel(t_img *img, int x, int y)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(int *)pixel);
}

int	inside_circle(t_mm mm, int x, int y)
{
	int	dx;
	int	dy;

	mm.radius += 10;
	dx = x - mm.cx;
	dy = y - mm.cy;
	return (square(dx) + square(dy) <= square(mm.radius));
}
