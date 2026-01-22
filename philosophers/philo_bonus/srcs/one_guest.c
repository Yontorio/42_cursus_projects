/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_guest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:50 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/09 07:03:01 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	lonely_dinner(t_rules *rules)
{
	printf("0\t1\tis thinking\n");
	sem_wait(rules->forks);
	printf("0\t1\thas taken a fork\n");
	usleep(rules->time_to_die * 1000);
	printf("%d\t1\tdied\n", rules->time_to_die);
	sem_post(rules->forks);
	sem_close(rules->forks);
	sem_unlink(SEM_FORKS);
	free(rules);
	exit(DEATH);
}

void	one_guest(t_rules *rules)
{
	pid_t	pid;

	sem_unlink(SEM_FORKS);
	rules->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, 1);
	if (rules->forks == SEM_FAILED)
		error(SEM_ERR, rules);
	pid = fork();
	if (pid < 0)
		error(FORK_ERR, rules);
	if (pid == 0)
		lonely_dinner(rules);
	waitpid(pid, NULL, 0);
	sem_close(rules->forks);
	sem_unlink(SEM_FORKS);
	free(rules);
	exit(EXIT_SUCCESS);
}
