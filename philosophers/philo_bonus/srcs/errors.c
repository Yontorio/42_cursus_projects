/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:42 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/10 14:39:40 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error(t_type err_type, t_rules *rules)
{
	const char	*msg = "";

	if (rules)
		clean_up(rules);
	if (err_type == INVALID_RULES)
		msg = "Invalid Rules!\n";
	else if (err_type == MALLOC_ERR)
		msg = "Memory allocation failed\n";
	else if (err_type == SEM_ERR)
		msg = "semaphore failure\n";
	else if (err_type == FORK_ERR)
		msg = "Failed to fork a child\n";
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}
