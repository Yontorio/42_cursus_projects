/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:01 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/04 09:31:08 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	done_eating(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

static bool	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (!philo_printer(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->first_fork), false);
	pthread_mutex_lock(philo->second_fork);
	if (!philo_printer(philo, "has taken a fork"))
		return (done_eating(philo), false);
	return (true);
}

static bool	meals_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	if (!am_i_full(philo))
		return (false);
	return (true);
}

bool	dinner_time(t_philo *philo)
{
	long	start;
	long	to_sleep;

	if (!pick_up_forks(philo))
		return (false);
	start = current_time();
	update_meal(philo, start);
	if (!philo_printer(philo, "is eating"))
		return (done_eating(philo), false);
	to_sleep = philo->rules->time_to_eat;
	if (!sleep_awake(philo, start, to_sleep))
		return (done_eating(philo), false);
	if (!meals_check(philo))
		return (done_eating(philo), false);
	done_eating(philo);
	return (true);
}
