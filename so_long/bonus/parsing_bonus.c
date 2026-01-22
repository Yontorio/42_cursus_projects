/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:42:37 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/07 02:25:59 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	**duplicate_map(char **map)
{
	char	**new;
	int		size;
	int		j;

	size = size_map(map);
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	j = 0;
	while (map[j])
	{
		new[j] = ft_strdup(map[j]);
		if (!new[j])
			return (free_map(new), NULL);
		j++;
	}
	new[j] = NULL;
	return (new);
}

static char	**split_lines(char *file)
{
	char	**map;

	if (newlines_check(file))
	{
		free(file);
		ft_putstr_fd("Error\nInvalid newline in map\n", 2);
		exit(1);
	}
	map = ft_split(file, '\n');
	if (!map)
	{
		perror("Error\nMemory");
		free(file);
		exit(1);
	}
	return (map);
}

static int	safe_read(int fd, char *buffer, int size, char *tmp)
{
	int	i;

	i = read(fd, buffer, size);
	if (i < 0)
	{
		if (tmp)
			free(tmp);
		perror("Error\nread ");
		exit(1);
	}
	return (i);
}

static char	*read_file(int fd)
{
	char	line[51];
	char	*tmp;
	char	*swap;
	int		i;

	i = safe_read(fd, line, 50, NULL);
	if (!i)
		return (ft_putendl_fd("Error\nMap is empty", 2), NULL);
	line[i] = '\0';
	tmp = NULL;
	while (i > 0)
	{
		swap = tmp;
		tmp = ft_strjoin(swap, line);
		free(swap);
		if (!tmp)
			return (perror("Error\nMemory "), exit(1), NULL);
		i = safe_read(fd, line, 50, tmp);
		if (i < 1)
			break ;
		line[i] = '\0';
	}
	return (tmp);
}

char	**parse_map(char *name)
{
	char	**dup_map;
	char	**map;
	char	*file;
	int		fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\n", 2), perror(name), NULL);
	file = read_file(fd);
	if (!file)
		return (NULL);
	close(fd);
	map = split_lines(file);
	free(file);
	map_check(map);
	dup_map = duplicate_map(map);
	if (!dup_map)
		return (free_map(map), perror("Error\nMemory"), NULL);
	if (!check_map_valide(dup_map))
		exit_error(map, "Error\nway to exit or colletibles is closed!\n");
	return (map);
}
