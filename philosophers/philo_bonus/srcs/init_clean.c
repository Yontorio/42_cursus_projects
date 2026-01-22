/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:45 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/10 14:46:13 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_up(t_rules *rules)
{
	if (rules->forks)
	{
		sem_close(rules->forks);
		sem_unlink(SEM_FORKS);
	}
	if (rules->print)
	{
		sem_close(rules->print);
		sem_unlink(SEM_PRINT);
	}
	if (rules->begin)
	{
		sem_close(rules->begin);
		sem_unlink(SEM_BEGIN);
	}
	if (rules->pids)
		free(rules->pids);
	if (rules->philo)
		free(rules->philo);
	free(rules);
}

static int	compute_half(int n_p)
{
	if (n_p % 2 == 1)
		return ((n_p - 1) / 2);
	else
		return (n_p / 2);
	return (0);
}

void	rules_setting(t_rules **rules, int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		error(INVALID_RULES, NULL);
	*rules = malloc(sizeof(t_rules));
	if (!(*rules))
		error(MALLOC_ERR, NULL);
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
		error(INVALID_RULES, NULL);
}

void	prepare_table(t_rules *rules)
{
	int	n_p;

	n_p = rules->num_of_philos;
	rules->half = compute_half(n_p);
	rules->pids = malloc(sizeof(pid_t) * n_p);
	if (!rules->pids)
		error(MALLOC_ERR, rules);
	sem_unlink(SEM_BEGIN);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	rules->begin = sem_open(SEM_BEGIN, O_CREAT | O_EXCL, 0644, 0);
	rules->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, n_p);
	rules->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (rules->begin == SEM_FAILED || rules->forks == SEM_FAILED
		|| rules->print == SEM_FAILED)
		error(SEM_ERR, rules);
	rules->type = NOT_YET;
}

void	get_philo_ready(t_rules *rules, int idx)
{
	rules->philo = malloc(sizeof(t_philo));
	if (!rules->philo)
		error(MALLOC_ERR, rules);
	rules->philo->id = idx + 1;
	rules->philo->meals_eaten = 0;
	rules->philo->last_meal = 0;
	return ;
}
