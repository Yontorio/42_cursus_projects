/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:07:28 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 17:14:26 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_values(double dx, double dy, double px, double py)
{
	t_maze	*maze;

	maze = (*maze_struct());
	maze->map.player.dir.x = dx;
	maze->map.player.dir.y = dy;
	maze->map.player.plane.x = px;
	maze->map.player.plane.y = py;
}

static void	get_directions(char dir)
{
	if (dir == 'N')
	{
		set_values(0, -1, FOV_ANGLE, 0);
	}
	else if (dir == 'S')
	{
		set_values(0, 1, -FOV_ANGLE, 0);
	}
	else if (dir == 'E')
	{
		set_values(1, 0, 0, FOV_ANGLE);
	}
	else if (dir == 'W')
	{
		set_values(-1, 0, 0, -FOV_ANGLE);
	}
}

static int	handle_player_spawn(t_map *map, int x, int y, char dir)
{
	map->player.pos.x = x + 0.5;
	map->player.pos.y = y + 0.5;
	get_directions(dir);
	map->grid[y][x] = '0';
	return (1);
}

void	parse_player(t_map *map)
{
	int		x;
	int		y;
	char	dir;
	int		found;

	y = 0;
	found = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			dir = map->grid[y][x];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				if (found)
					error_exit("Multiple player spawn points");
				found = handle_player_spawn(map, x, y, dir);
			}
			x++;
		}
		y++;
	}
	if (!found)
		error_exit("No player spawn found in map");
}
