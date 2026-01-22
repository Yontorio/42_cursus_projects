/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:14:02 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/07 22:22:39 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_pos	find_position(char **map, char c)
{
	t_pos	pos;
	int		i;
	int		j;

	i = 0;
	pos.row = -1;
	pos.col = -1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
			{
				pos.row = i;
				pos.col = j;
			}
			j++;
		}
		i++;
	}
	return (pos);
}

static void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == '1')
		return ;
	map[y][x] = '1';
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
}

int	check_map_valide(char **map)
{
	t_pos	pos;
	int		x;
	int		y;

	pos = find_position(map, 'P');
	flood_fill(map, pos.row, pos.col);
	y = 0;
	while (map[y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == 'E' || map[y][x] == 'C')
				return (free_map(map), 0);
		y++;
	}
	free_map(map);
	return (1);
}
