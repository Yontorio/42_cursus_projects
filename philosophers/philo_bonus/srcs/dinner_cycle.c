/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:39 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/09 07:02:48 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	bed_time(t_rules *rules)
{
	long	start;

	start = current_time();
	philo_printer(rules, "is sleeping");
	sleep_awake(rules, start, rules->time_to_sleep);
}

static void	am_i_full(t_rules *rules)
{
	if (rules->num_of_meals > 0)
	{
		if (rules->philo->meals_eaten >= rules->num_of_meals)
		{
			clean_up(rules);
			exit(FULL);
		}
	}
}

static void	pick_up_forks(t_rules *rules)
{
	sem_wait(rules->forks);
	philo_printer(rules, "has taken a fork");
	sem_wait(rules->forks);
	philo_printer(rules, "has taken a fork");
}

static void	done_eating(t_rules *rules)
{
	rules->philo->meals_eaten++;
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	dinner_time(t_rules *rules)
{
	long	start;

	pick_up_forks(rules);
	philo_printer(rules, "is eating");
	start = current_time();
	rules->philo->last_meal = start;
	sleep_awake(rules, start, rules->time_to_eat);
	done_eating(rules);
	am_i_full(rules);
}
