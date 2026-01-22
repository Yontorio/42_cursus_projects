/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 08:26:49 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/09 09:19:24 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	death_situation(t_rules *rules, long time)
{
	if (rules->time_to_die <= (current_time() - rules->philo->last_meal))
	{
		printf("%ld\t%d\t%s\n", time, rules->philo->id, "died");
		clean_up(rules);
		exit(DEATH);
	}
}

void	philo_printer(t_rules *rules, const char *msg)
{
	long	time;

	sem_wait(rules->print);
	time = current_time() - rules->start_time;
	death_situation(rules, time);
	printf("%ld\t%d\t%s\n", time, rules->philo->id, msg);
	sem_post(rules->print);
}

void	death_printer(t_rules *rules, const char *msg)
{
	long	time;

	time = current_time() - rules->start_time;
	sem_wait(rules->print);
	printf("%ld\t%d\t%s\n", time, rules->philo->id, msg);
}
