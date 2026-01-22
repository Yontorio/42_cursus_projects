/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:16:43 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/07 22:10:27 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	char	**map;

	if (ac != 2)
		return (ft_putstr_fd("Error\nparameter needed\n", 2), 1);
	if (!file_name_check(av[1]))
		return (ft_putstr_fd("Error\ninvalide map name.\n", 2), 1);
	map = parse_map(av[1]);
	if (!map)
		return (1);
	mlx_set_up(map);
	return (0);
}
