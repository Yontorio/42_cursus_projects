/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:25:50 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 19:26:30 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_texture_id(char *id)
{
	return (!ft_strcmp(id, "NO") || !ft_strcmp(id, "SO") || !ft_strcmp(id, "WE")
		|| !ft_strcmp(id, "EA"));
}

static void	set_texture(char *id, char *path)
{
	t_env	*env;

	env = &((*maze_struct())->env);
	if (!ft_strcmp(id, "NO"))
		env->no = ft_strndup(path, ft_strlen(path));
	else if (!ft_strcmp(id, "SO"))
		env->so = ft_strndup(path, ft_strlen(path));
	else if (!ft_strcmp(id, "WE"))
		env->we = ft_strndup(path, ft_strlen(path));
	else if (!ft_strcmp(id, "EA"))
		env->ea = ft_strndup(path, ft_strlen(path));
}

void	parse_texture_line(char *line)
{
	char	**parts;

	parts = split_one_time(line);
	if (!parts || !parts[0] || !parts[1])
		error_exit("Invalid texture line");
	if (!is_texture_id(parts[0]))
		error_exit("Unknown texture identifier");
	set_texture(parts[0], parts[1]);
}

int	is_valid_rgb(int n)
{
	return (n >= 0 && n <= 255);
}
