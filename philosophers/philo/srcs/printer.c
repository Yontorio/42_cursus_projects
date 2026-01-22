/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:15 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/04 13:27:15 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_printer(t_philo *philo)
{
	long	time;
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&rules->printer);
	if (get_status(philo->rules) != BEGAN)
	{
		pthread_mutex_unlock(&rules->printer);
		return ;
	}
	set_status(rules, DEATH);
	time = current_time() - rules->start_time;
	printf("%ld\t%d\t%s\n", time, philo->id, "died");
	pthread_mutex_unlock(&rules->printer);
}

static bool	death_situation(t_philo *philo, char **msg)
{
	t_rules	*rules;
	long	elapse;

	rules = philo->rules;
	pthread_mutex_lock(&philo->meal_lock);
	elapse = current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if (elapse >= rules->time_to_die)
		return (set_status(rules, DEATH), *msg = "died", false);
	return (true);
}

bool	philo_printer(t_philo *philo, char *msg)
{
	t_rules	*rules;
	bool	state;
	long	time;

	rules = philo->rules;
	pthread_mutex_lock(&rules->printer);
	time = current_time() - rules->start_time;
	if (get_status(philo->rules) != BEGAN)
		return (pthread_mutex_unlock(&rules->printer), false);
	state = death_situation(philo, &msg);
	printf("%ld\t%d\t%s\n", time, philo->id, msg);
	pthread_mutex_unlock(&rules->printer);
	return (state);
}
