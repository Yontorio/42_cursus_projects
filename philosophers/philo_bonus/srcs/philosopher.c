/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:52 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/10 13:07:39 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	am_i_dead(t_rules *rules)
{
	long	elapse;

	elapse = current_time() - rules->philo->last_meal;
	if (elapse >= rules->time_to_die)
	{
		death_printer(rules, "died");
		clean_up(rules);
		exit(DEATH);
	}
	return (true);
}

static void	think_time(t_rules *rules)
{
	long	think_time;
	long	start;

	philo_printer(rules, "is thinking");
	if (rules->time_to_eat < rules->time_to_sleep
		|| !(rules->num_of_philos % 2))
		return ;
	start = current_time();
	think_time = (rules->time_to_eat * 2) - rules->time_to_sleep;
	sleep_awake(rules, start, think_time);
}

static void	think_and_wait(t_rules *rules)
{
	long	start;
	long	delay;

	philo_printer(rules, "is thinking");
	if (rules->type == FIRST_GP)
		return ;
	start = current_time();
	delay = rules->time_to_eat;
	if (rules->type == THIRD_GR)
		delay *= 2;
	sleep_awake(rules, start, delay);
}

static void	wait_for_start(t_rules *rules)
{
	sem_wait(rules->begin);
	while (current_time() - rules->start_time < MAGIC_NUMBER)
		usleep(MAGIC_NUMBER);
	rules->start_time += MAGIC_NUMBER;
	rules->philo->last_meal = rules->start_time;
}

void	the_philosopher(t_rules *rules, int idx)
{
	get_philo_ready(rules, idx);
	wait_for_start(rules);
	think_and_wait(rules);
	while (am_i_dead(rules))
	{
		dinner_time(rules);
		bed_time(rules);
		think_time(rules);
	}
}
