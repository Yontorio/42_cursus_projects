/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:54:43 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 17:54:44 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_maze	**maze_struct(void)
{
	static t_maze	*maze = NULL;

	if (maze == NULL)
	{
		init_maze(&maze);
	}
	return (&maze);
}
