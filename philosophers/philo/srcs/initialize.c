/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:03:30 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/10 11:57:05 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	rules_setting(t_rules **rules, int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		return (error(INVALID_RULES, NULL));
	*rules = malloc(sizeof(t_rules));
	if (!(*rules))
		return (error(MALLOC_ERR, NULL));
	memset(*rules, 0, sizeof(t_rules));
	(argv++);
	(*rules)->num_of_philos = ato_rule(*argv++);
	(*rules)->time_to_die = ato_rule(*argv++);
	(*rules)->time_to_eat = ato_rule(*argv++);
	(*rules)->time_to_sleep = ato_rule(*argv++);
	(*rules)->num_of_meals = ato_rule(*argv);
	if ((*rules)->num_of_philos <= 0 || (*rules)->time_to_die <= 0
		|| (*rules)->time_to_eat <= 0 || (*rules)->time_to_sleep <= 0 || (*argv
			&& (*rules)->num_of_meals <= 0))
		return (error(INVALID_RULES, NULL));
	return (EXIT_SUCCESS);
}

int	prepare_table(t_rules *rules)
{
	int	n_p;

	n_p = rules->num_of_philos;
	rules->philos = malloc(sizeof(t_philo) * n_p);
	if (!rules->philos)
		return (error(MALLOC_ERR, rules));
	memset(rules->philos, 0, sizeof(t_philo) * n_p);
	rules->forks = malloc(sizeof(pthread_mutex_t) * n_p);
	if (!rules->forks)
		return (error(MALLOC_ERR, rules));
	memset(rules->forks, 0, sizeof(pthread_mutex_t) * n_p);
	while (n_p--)
		if (pthread_mutex_init(&rules->forks[n_p], NULL)
			|| pthread_mutex_init(&rules->philos[n_p].meal_lock, NULL))
			return (error(PTRD_MTX_INIT_ERR, rules));
	if (pthread_mutex_init(&rules->printer, NULL)
		|| pthread_mutex_init(&rules->state_lock, NULL)
		|| pthread_mutex_init(&rules->order_lock, NULL))
		return (error(PTRD_MTX_INIT_ERR, rules));
	rules->state = NOT_YET;
	rules->order = WAIT;
	return (EXIT_SUCCESS);
}

static void	forks_to_pick_up(t_rules *rules, t_philo *philo, int idx)
{
	if (rules->num_of_philos != philo->id)
	{
		philo->first_fork = &rules->forks[idx];
		philo->second_fork = &rules->forks[++idx];
		return ;
	}
	philo->first_fork = &rules->forks[0];
	philo->second_fork = &rules->forks[idx];
}

int	seat_philos(t_rules *rules)
{
	t_philo	*cur_philo;
	int		n_p;
	int		i;

	i = 0;
	n_p = rules->num_of_philos;
	while (i < n_p)
	{
		cur_philo = &(rules->philos)[i];
		cur_philo->id = i + 1;
		cur_philo->type = WAIT;
		cur_philo->is_full = NOT_YET;
		cur_philo->rules = rules;
		cur_philo->last_meal = 0;
		cur_philo->meals_eaten = 0;
		forks_to_pick_up(rules, cur_philo, i++);
	}
	return (EXIT_SUCCESS);
}
