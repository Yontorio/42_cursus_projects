/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:14:54 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/07 23:22:34 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_images(t_data *data)
{
	int	i;

	i = 0;
	while (data->img[i])
	{
		mlx_destroy_image(data->mlx, data->img[i]);
		i++;
	}
}

int	close_window(t_data *data)
{
	destroy_images(data);
	free_map(data->map);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(1);
	return (0);
}

void	exit_game(t_data *data, char **map, char *msg, int type)
{
	if (!type)
		ft_putstr_fd(msg, 2);
	else if (type == WIN)
	{
		print_moves(data);
		ft_putendl_fd("\nVictory is yours! Well done! (^‿^)", 1);
		if (data)
			close_window(data);
		else
			free_map(map);
		exit(0);
	}
	if (data)
		close_window(data);
	else
		free_map(map);
	exit(1);
}

void	clean(t_data *data, int code)
{
	ft_putstr_fd("Error\n", 2);
	perror("texture ");
	if (data->mlx)
	{
		destroy_images(data);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	free_map(data->map);
	exit(code);
}
