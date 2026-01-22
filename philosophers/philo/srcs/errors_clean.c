/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:03 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/10 13:06:18 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(t_status status, t_rules *rules)
{
	const char	*msg = "";

	if (rules)
		clean_up(rules);
	if (status == INVALID_RULES)
		msg = "Invalid Rules!\n";
	else if (status == MALLOC_ERR)
		msg = "Memory allocation failed\n";
	else if (status == PTRD_CREATE_ERR)
		msg = "Failed to create thread\n";
	else if (status == PTRD_MTX_INIT_ERR)
		msg = "Failed to initialize mutex\n";
	write(2, msg, ft_strlen(msg));
	return (EXIT_FAILURE);
}

int	creation_error(t_rules *rules, int n_p)
{
	rules->state = PTRD_CREATE_ERR;
	pthread_mutex_unlock(&rules->state_lock);
	if (n_p != rules->num_of_philos)
	{
		while ((++n_p) < rules->num_of_philos)
			pthread_join(rules->philos[n_p].thread, NULL);
		pthread_join(rules->butler, NULL);
	}
	return (error(PTRD_CREATE_ERR, rules));
}

void	clean_up(t_rules *rules)
{
	int	n_p;

	n_p = rules->num_of_philos;
	if (rules->forks)
	{
		while (n_p--)
			pthread_mutex_destroy(&rules->forks[n_p]);
		free(rules->forks);
	}
	pthread_mutex_destroy(&rules->printer);
	pthread_mutex_destroy(&rules->state_lock);
	pthread_mutex_destroy(&rules->order_lock);
	if (rules->philos)
	{
		n_p = rules->num_of_philos;
		while (n_p--)
			pthread_mutex_destroy(&rules->philos[n_p].meal_lock);
		free(rules->philos);
	}
	free(rules);
}
