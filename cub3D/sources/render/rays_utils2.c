/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:12:52 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 17:22:54 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec	v_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y});
}

t_vec	v_scale(t_vec v, double s)
{
	return ((t_vec){v.x * s, v.y * s});
}
