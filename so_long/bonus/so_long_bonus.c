/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:43:16 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/03 18:51:19 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;
	char	**map;

	if (ac != 2)
		return (ft_putstr_fd("Error\nparameter needed\n", 2), 1);
	if (!file_name_check(av[1]))
		return (ft_putstr_fd("Error\ninvalide map name.\n", 2), 1);
	map = parse_map(av[1]);
	if (!map)
		return (1);
	mlx_set_up(&data, map);
	mlx_loop(data.mlx);
	return (0);
}
