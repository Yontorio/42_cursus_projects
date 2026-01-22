/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   butler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:03:55 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/10 13:06:08 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_order	next_order(t_rules *rules, t_order curr_order)
{
	bool	is_odd;

	is_odd = rules->num_of_philos % 2;
	if (curr_order == ODDS)
		return (EVENS);
	else if (curr_order == EVENS && is_odd)
		return (LAST);
	else if (curr_order == LAST)
		return (ODDS);
	return (ODDS);
}

static bool	grim_reaper(t_rules *rules, t_philo *philo)
{
	long	since;

	pthread_mutex_lock(&philo->full_lock);
	pthread_mutex_lock(&philo->meal_lock);
	since = current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if (since >= rules->time_to_die && philo->is_full != FULL
		&& get_status(rules) == BEGAN)
	{
		pthread_mutex_unlock(&philo->full_lock);
		death_printer(philo);
		return (false);
	}
	pthread_mutex_unlock(&philo->full_lock);
	return (true);
}

static long	time_to_wait(t_rules *rules, t_order order)
{
	unsigned long	eat_time;
	unsigned long	sleep_time;

	eat_time = rules->time_to_eat;
	sleep_time = rules->time_to_sleep;
	if (sleep_time <= eat_time
		|| next_order(rules, order) != ODDS
		|| sleep_time <= eat_time * order)
		return (eat_time);
	return (eat_time + sleep_time - (eat_time * order));
}

static bool	waiter_loop(t_rules *rules, t_order	order, long start)
{
	bool	one_time;
	int		n_p;

	one_time = true;
	while (time_to_wait(rules, order) > current_time() - start
		&& get_status(rules) == BEGAN)
	{
		usleep(CHECK_PRECISION);
		n_p = rules->num_of_philos;
		while (n_p--)
			if (!grim_reaper(rules, &rules->philos[n_p]))
				return (false);
		if (one_time)
		{
			if (rules->num_of_meals > 0 && all_full(rules))
				return (false);
			one_time = false;
		}
	}
	return (true);
}

void	*the_butler(void *arg)
{
	t_rules		*rules;
	t_order		order;
	int			n_p;

	rules = (t_rules *)arg;
	if (get_status(rules) == PTRD_CREATE_ERR)
		return (NULL);
	n_p = rules->num_of_philos;
	rules->start_time = current_time();
	while (n_p--)
		update_meal(&rules->philos[n_p], rules->start_time);
	while (get_status(rules) == BEGAN)
	{
		order = next_order(rules, get_order(rules));
		set_order(rules, order);
		if (!waiter_loop(rules, order, current_time()))
			return (NULL);
	}
	return (NULL);
}
