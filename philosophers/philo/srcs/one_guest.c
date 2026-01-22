/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_guest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:13 by ahoummad          #+#    #+#             */
/*   Updated: 2025/07/31 07:04:14 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*lonely_dinner(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	printf("0\t1\tis thinking\n");
	pthread_mutex_lock(rules->forks);
	printf("0\t1\thas taken a fork\n");
	usleep(rules->time_to_die * 1000);
	printf("%d\t1\tdied\n", rules->time_to_die);
	pthread_mutex_unlock(rules->forks);
	return (NULL);
}

int	one_guest(t_rules *rules)
{
	pthread_t	philo_thread;

	rules->forks = malloc(sizeof(pthread_mutex_t));
	if (!rules->forks)
		return (error(MALLOC_ERR, rules));
	if (pthread_mutex_init(rules->forks, NULL))
		return (error(PTRD_MTX_INIT_ERR, rules));
	if (pthread_create(&philo_thread, NULL, lonely_dinner, rules))
		return (error(PTRD_CREATE_ERR, rules));
	pthread_join(philo_thread, NULL);
	pthread_mutex_destroy(rules->forks);
	free(rules->forks);
	free(rules);
	return (EXIT_SUCCESS);
}
