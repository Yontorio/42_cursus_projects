/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 18:40:51 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 18:40:55 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	safe_read(int fd, char *buffer, int size)
{
	int	i;

	i = read(fd, buffer, size);
	if (i < 0)
	{
		error_exit("Read failure");
	}
	return (i);
}

static char	*read_loop(int fd, char *been_read)
{
	char	buffer[51];
	int		i;

	while (true)
	{
		i = safe_read(fd, buffer, 50);
		if (!i)
			break ;
		buffer[i] = '\0';
		been_read = join_two_strings(been_read, buffer, "");
	}
	fd_storage(CLOSE);
	return (been_read);
}

char	*read_file(char *file_path)
{
	char	buffer[51];
	int		fd;
	int		i;

	fd = safe_open(file_path, O_RDONLY);
	i = safe_read(fd, buffer, 50);
	if (i == 0)
	{
		error_exit("Config file is empty");
	}
	buffer[i] = '\0';
	return (read_loop(fd, ft_strdup(buffer)));
}
