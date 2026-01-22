/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:14:11 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/07 22:22:52 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_map_len(char **lines)
{
	int	len;
	int	i;

	if (!lines || !lines[0])
		return (1);
	len = ft_strlen(lines[0]);
	i = 1;
	while (lines[i])
	{
		if ((int)ft_strlen(lines[i]) != len)
			return (0);
		i++;
	}
	return (1);
}

static int	wall_check(char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	check_line(char *src, t_state *state)
{
	int	i;

	if (src[0] != '1' || src[ft_strlen(src) - 1] != '1')
		return (0);
	i = 1;
	while (src[i])
	{
		if (src[i] == 'P')
			state->position++;
		else if (src[i] == 'C')
			state->collectible++;
		else if (src[i] == 'E')
			state->exit++;
		else if (src[i] != '1' && src[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

void	exit_error(char **map, char *msg)
{
	ft_putstr_fd(msg, 2);
	free_map(map);
	exit(1);
}

void	map_check(char **map)
{
	int		i;
	t_state	state;

	state.collectible = 0;
	state.position = 0;
	state.exit = 0;
	i = 0;
	if (!check_map_len(map))
		exit_error(map, "Error\nlines not equals in map.\n");
	if (!wall_check(map[0]))
		exit_error(map, "Error\nInvalid wall in map.\n");
	while (map[i] && map[i + 1])
		if (!check_line(map[i++], &state))
			exit_error(map, "Error\nInvalid map structure.\n");
	if (!wall_check(map[i]))
		exit_error(map, "Error\nInvalid wall in map.\n");
	if (state.position != 1)
		exit_error(map, "Error\nInvalid number of characters.\n");
	if (state.exit != 1)
		exit_error(map, "Error\nInvalid number of exit.\n");
	if (state.collectible < 1)
		exit_error(map, "Error\nNo collectible in map.\n");
}
