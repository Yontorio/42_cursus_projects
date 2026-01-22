/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:13:40 by ahoummad          #+#    #+#             */
/*   Updated: 2025/04/03 18:13:41 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	file_name_check(char *param)
{
	char	*tmp;
	int		param_len;

	param_len = ft_strlen(param);
	if (param_len <= 4)
		return (0);
	tmp = ft_strrchr(param, '/');
	if (tmp && ft_strlen(tmp) <= 5)
		return (0);
	else if (!ft_strncmp(param + (param_len - 4), ".ber", 4))
		return (1);
	return (0);
}
