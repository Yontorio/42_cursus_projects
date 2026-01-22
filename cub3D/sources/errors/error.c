/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:31:56 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 19:32:07 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	error_exit(char *error_msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
	fd_storage(CLOSE);
	destroy_maze();
	destroy_everything();
	exit(EXIT_FAILURE);
}
