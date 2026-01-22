/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:06 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/08 10:00:09 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_meal(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->meal_lock);
}

t_status	get_status(t_rules *rules)
{
	t_status	state;

	pthread_mutex_lock(&rules->state_lock);
	state = rules->state;
	pthread_mutex_unlock(&rules->state_lock);
	return (state);
}

void	set_status(t_rules *rules, t_status state)
{
	pthread_mutex_lock(&rules->state_lock);
	rules->state = state;
	pthread_mutex_unlock(&rules->state_lock);
}

t_order	get_order(t_rules *rules)
{
	t_order	order;

	pthread_mutex_lock(&rules->order_lock);
	order = rules->order;
	pthread_mutex_unlock(&rules->order_lock);
	return (order);
}

void	set_order(t_rules *rules, t_order order)
{
	pthread_mutex_lock(&rules->order_lock);
	rules->order = order;
	pthread_mutex_unlock(&rules->order_lock);
}
