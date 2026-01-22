/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   butler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:37 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/10 14:45:45 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	grim_reaper(t_rules *rules)
{
	int	n_p;

	n_p = rules->num_of_philos;
	while (n_p--)
		kill(rules->pids[n_p], SIGKILL);
	n_p = rules->num_of_philos;
	while (n_p--)
		waitpid(rules->pids[n_p], NULL, 0);
	return ;
}

static void	child_error(t_rules *rules)
{
	grim_reaper(rules);
	clean_up(rules);
	exit(EXIT_FAILURE);
}

void	the_butler(t_rules *rules)
{
	int	philo_full;
	int	status;
	int	code;

	philo_full = 0;
	while (philo_full < rules->num_of_philos)
	{
		waitpid(-1, &status, 0);
		code = WEXITSTATUS(status);
		if (code == FULL)
			philo_full++;
		else if (code == DEATH)
			return (grim_reaper(rules));
		else
			return (child_error(rules));
	}
	return ;
}
