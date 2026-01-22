/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:34 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/10 14:20:24 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	creation_error(t_rules *rules, int alive_philos)
{
	int	idx;

	idx = 0;
	while (idx < alive_philos)
		kill(rules->pids[idx++], SIGKILL);
	idx = 0;
	while (idx < alive_philos)
		waitpid(rules->pids[idx++], NULL, 0);
	return (error(FORK_ERR, rules));
}

static int	fork_group(t_rules *rules, t_type gr_type, int idx, int count)
{
	pid_t	pid;

	rules->type = gr_type;
	while (idx < count)
	{
		pid = fork();
		if (pid < 0)
			creation_error(rules, idx);
		if (pid == 0)
			the_philosopher(rules, idx);
		rules->pids[idx++] = pid;
		usleep(MAGIC_NUMBER);
	}
	return (EXIT_SUCCESS);
}

static void	seat_philos(t_rules *rules)
{
	int	half;
	int	n_p;

	half = rules->half;
	n_p = rules->num_of_philos;
	rules->start_time = current_time();
	fork_group(rules, FIRST_GP, 0, half);
	fork_group(rules, SECOND_GR, half, (half * 2));
	if (n_p % 2)
		fork_group(rules, THIRD_GR, (n_p - 1), n_p);
}

void	begin_simulation(t_rules *rules)
{
	int	n_p;

	n_p = rules->num_of_philos;
	seat_philos(rules);
	while (n_p--)
		sem_post(rules->begin);
	the_butler(rules);
	clean_up(rules);
	exit(EXIT_SUCCESS);
}
