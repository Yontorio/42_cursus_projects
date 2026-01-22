/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:18 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/04 11:20:06 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_full(t_rules *rules)
{
	t_philo	*cur_philo;
	int		n_p;

	n_p = rules->num_of_philos;
	while (n_p--)
	{
		cur_philo = &rules->philos[n_p];
		pthread_mutex_lock(&cur_philo->full_lock);
		if (cur_philo->is_full != FULL)
			return (pthread_mutex_unlock(&cur_philo->full_lock), false);
		pthread_mutex_unlock(&cur_philo->full_lock);
	}
	set_status(rules, FULL);
	return (true);
}

static bool	am_i_dead(t_philo *philo)
{
	t_rules	*rules;
	long	since;

	rules = philo->rules;
	pthread_mutex_lock(&philo->meal_lock);
	since = current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if (since >= rules->time_to_die)
	{
		if (get_status(rules) == BEGAN)
			death_printer(philo);
		return (false);
	}
	return (true);
}

bool	am_i_full(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&philo->meal_lock);
	if (rules->num_of_meals > 0 && philo->meals_eaten >= rules->num_of_meals)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		pthread_mutex_lock(&philo->full_lock);
		philo->is_full = FULL;
		pthread_mutex_unlock(&philo->full_lock);
		return (false);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (true);
}

bool	death_check(t_philo *philo)
{
	if (get_status(philo->rules) != BEGAN)
		return (false);
	if (!am_i_dead(philo))
		return (false);
	return (true);
}
