/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_anime_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:19:21 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/06 03:38:20 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	animation(t_data *data, void *img)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'V')
				mlx_put_image_to_window(data->mlx, data->win, img, x * SIZE, y
					* SIZE);
			x++;
		}
		y++;
	}
}

int	enemy(t_data *data)
{
	struct timeval	tv;
	void			*img;
	size_t			curr_t;
	static int		i = 0;
	static size_t	last_t = 0;

	if (gettimeofday(&tv, NULL) == -1)
		exit_game(data, data->map, "gettimeofday", 2);
	curr_t = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (curr_t - last_t >= DELAY)
	{
		img = data->enemy[i];
		animation(data, img);
		i = (i + 1) % 8;
		last_t = curr_t;
	}
	return (0);
}
