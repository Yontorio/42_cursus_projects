/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:59:36 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/12 13:07:54 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_maze *maze)
{
	char	*tex_paths[6];
	int		i;

	i = -1;
	tex_paths[0] = maze->env.no;
	tex_paths[1] = maze->env.so;
	tex_paths[2] = maze->env.we;
	tex_paths[3] = maze->env.ea;
	tex_paths[4] = ft_strdup("textures/wood.xpm");
	tex_paths[5] = ft_strdup("textures/bigcoin.xpm");
	while (++i < 6)
	{
		maze->tex[i].img = mlx_xpm_file_to_image(maze->mlx, tex_paths[i],
				&maze->tex[i].width, &maze->tex[i].height);
		if (!maze->tex[i].img)
			error_exit("Failed to load XPM texture");
		maze->tex[i].addr = mlx_get_data_addr(maze->tex[i].img,
				&maze->tex[i].bpp, &maze->tex[i].line_len,
				&maze->tex[i].endian);
	}
}
