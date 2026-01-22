/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:03:58 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/08 09:59:22 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	bed_time(t_philo *philo)
{
	long	to_sleep;
	long	start;

	start = current_time();
	to_sleep = philo->rules->time_to_sleep;
	if (!philo_printer(philo, "is sleeping"))
		return (false);
	return (sleep_awake(philo, start, to_sleep));
}

static bool	think_time(t_philo *philo)
{
	return (philo_printer(philo, "is thinking"));
}

static bool	before_start(t_rules *rules, t_philo *philo)
{
	if (get_status(rules) == PTRD_CREATE_ERR)
		return (false);
	while (get_order(rules) == WAIT)
		usleep(CHECK_PRECISION);
	return (think_time(philo));
}

void	*dinner_cycle(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	if (!before_start(rules, philo))
		return (NULL);
	while (death_check(philo))
	{
		if (get_order(rules) != philo->type)
		{
			usleep(CHECK_PRECISION);
			continue ;
		}
		if (!dinner_time(philo) || !bed_time(philo) || !think_time(philo))
			return (NULL);
	}
	return (NULL);
}
