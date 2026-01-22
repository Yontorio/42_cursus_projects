/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:31:20 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 19:31:29 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	if (config_parser(ac, av))
	{
		if (maze_setup())
		{
			return (eternal_maze());
		}
	}
	return (EXIT_FAILURE);
}
