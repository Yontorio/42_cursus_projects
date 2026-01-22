/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:36:01 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 19:36:02 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memtrack.h"

int	safe_open(const char *path, int flags)
{
	int	fd;

	fd = open(path, flags);
	if (fd == -1)
	{
		error_exit("File can not be opened");
	}
	fd_storage(fd);
	return (fd);
}

void	fd_storage(int fd)
{
	static int	stored_fd = -1;

	if (fd == CLOSE)
	{
		if (stored_fd != -1)
		{
			close(stored_fd);
			stored_fd = -1;
		}
	}
	else
	{
		stored_fd = fd;
	}
}
