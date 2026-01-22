/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:14:31 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/03 22:05:22 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_collec(char **map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
		count += count_char(map[i++], 'C');
	return (count);
}

int	newlines_check(char *str)
{
	int	i;

	if (str[0] == '\n')
		return (1);
	if (str[ft_strlen(str) - 1] == '\n')
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	count_char(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	size_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

void	free_map(char **map)
{
	int	i;

	if (map)
	{
		i = -1;
		while (map[++i])
			free(map[i]);
		free(map);
	}
}
