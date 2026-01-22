/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:07:33 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/11 13:32:51 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char **lines)
{
	int	count;

	count = 0;
	while (lines[count])
		count++;
	return (count);
}

int	get_max_width(char **map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

bool	is_map_line(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'C' || c == 'D' || c == 'd'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	normalize_map(t_map *map)
{
	int		max;
	int		i;
	int		len;
	char	*new_line;

	max = map->width;
	i = 0;
	while (map->grid[i])
	{
		len = ft_strlen(map->grid[i]);
		if (len < max)
		{
			new_line = ft_realloc(map->grid[i], len + 1, max + 1);
			ft_memset(new_line + len, ' ', max - len);
			new_line[max] = '\0';
			map->grid[i] = new_line;
		}
		i++;
	}
}

void	extract_map(char **lines)
{
	char	**grid;
	t_map	*map;
	int		i;
	int		map_lines;

	i = -1;
	map = &((*maze_struct())->map);
	map_lines = count_lines(lines);
	while (map_lines > 0 && lines[map_lines - 1][0] == '\0')
		map_lines--;
	grid = allocate_memory(sizeof(char *) * (map_lines + 1));
	while ((++i) < map_lines)
	{
		if (!lines[i][0])
			error_exit("Invalid line in map");
		grid[i] = ft_strdup(lines[i]);
	}
	grid[map_lines] = NULL;
	map->grid = grid;
	map->height = map_lines;
	map->width = get_max_width(map->grid);
	parse_player(map);
	normalize_map(map);
	check_map_chars(map);
	check_map_closed(map);
}
