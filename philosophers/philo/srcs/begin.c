/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:03:51 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/08 10:03:22 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_philos_types(t_philo *philo)
{
	int	n_p;

	n_p = philo->rules->num_of_philos;
	if (n_p % 2)
		philo[--n_p].type = LAST;
	while (n_p)
	{
		if ((n_p--) % 2)
			philo[n_p].type = ODDS;
		else
			philo[n_p].type = EVENS;
	}
}

static int	create_threads(t_rules *rules)
{
	t_philo	*p;
	int		n_p;

	p = rules->philos;
	n_p = rules->num_of_philos;
	if (pthread_create(&rules->butler, NULL, the_butler, rules))
		return (creation_error(rules, n_p));
	while (n_p--)
	{
		if (pthread_create(&(p[n_p].thread), NULL, dinner_cycle, &p[n_p]))
			return (creation_error(rules, n_p));
		usleep(10);
	}
	return (EXIT_SUCCESS);
}

static void	join_threads(t_rules *rules)
{
	int		n_p;
	t_philo	*p;

	p = rules->philos;
	n_p = rules->num_of_philos;
	while (n_p--)
		pthread_join(p[n_p].thread, NULL);
	pthread_join(rules->butler, NULL);
}

int	begin_simulation(t_rules *rules)
{
	set_philos_types(rules->philos);
	pthread_mutex_lock(&rules->state_lock);
	if (create_threads(rules))
		return (EXIT_FAILURE);
	rules->state = BEGAN;
	pthread_mutex_unlock(&rules->state_lock);
	join_threads(rules);
	clean_up(rules);
	return (EXIT_SUCCESS);
}
