/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:03:34 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/09 08:47:14 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_rules	t_rules;

# define CHECK_PRECISION 100
# define ONE_GUEST 1

typedef enum e_status
{
	NOT_YET,
	BEGAN,
	DEATH,
	FULL,
	MALLOC_ERR,
	INVALID_RULES,
	PTRD_CREATE_ERR,
	PTRD_MTX_INIT_ERR
}						t_status;

typedef enum e_order
{
	ODDS,
	EVENS,
	LAST,
	WAIT
}						t_order;

struct					s_rules
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_meals;
	long				start_time;
	t_order				order;
	t_status			state;
	t_philo				*philos;
	pthread_t			butler;
	pthread_mutex_t		*forks;
	pthread_mutex_t		printer;
	pthread_mutex_t		state_lock;
	pthread_mutex_t		order_lock;
};

struct					s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal;
	t_order				type;
	t_rules				*rules;
	t_status			is_full;
	pthread_t			thread;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		full_lock;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
};

int						ato_rule(char *s);
long					current_time(void);
void					*the_butler(void *arg);
size_t					ft_strlen(const char *s);
void					*dinner_cycle(void *arg);
void					clean_up(t_rules *rules);
bool					all_full(t_rules *rules);
bool					am_i_full(t_philo *philo);
int						one_guest(t_rules *rules);
t_order					get_order(t_rules *rules);
t_status				get_status(t_rules *rules);
int						seat_philos(t_rules *rules);
bool					dinner_time(t_philo *philo);
bool					death_check(t_philo *philo);
void					death_printer(t_philo *philo);
int						prepare_table(t_rules *rules);
int						begin_simulation(t_rules *rules);
int						error(t_status status, t_rules *rules);
void					update_meal(t_philo *philo, long time);
int						creation_error(t_rules *rules, int n_p);
void					set_order(t_rules *rules, t_order order);
void					set_status(t_rules *rules, t_status state);
bool					philo_printer(t_philo *philo, char *msg);
int						rules_setting(t_rules **rules, int argc, char **argv);
bool					sleep_awake(t_philo *philo, long start, long to_sleep);

#endif