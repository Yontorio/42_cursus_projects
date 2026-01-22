/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:30 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/09 09:18:19 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define SEM_FORKS "/forks"
# define SEM_PRINT "/printer"
# define SEM_BEGIN "/begin"
# define CHECK_PRECISION 100
# define MAGIC_NUMBER 10
# define ONE_GUEST 1

typedef struct s_philo	t_philo;
typedef struct s_rules	t_rules;

typedef enum e_type
{
	NOT_YET,
	FIRST_GP,
	SECOND_GR,
	THIRD_GR,
	BEGAN,
	DEATH,
	FULL,
	SEM_ERR,
	FORK_ERR,
	MALLOC_ERR,
	INVALID_RULES,
}						t_type;

struct					s_rules
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_meals;
	long				start_time;
	int					half;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*begin;
	pid_t				*pids;
	t_type				type;
	t_philo				*philo;
};

struct					s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal;
};

int						ato_rule(char *s);
long					current_time(void);
size_t					ft_strlen(const char *s);
void					bed_time(t_rules *rules);
void					clean_up(t_rules *rules);
bool					am_i_dead(t_rules *rules);
void					one_guest(t_rules *rules);
void					the_butler(t_rules *rules);
void					dinner_time(t_rules *rules);
void					prepare_table(t_rules *rules);
void					begin_simulation(t_rules *rules);
void					error(t_type type, t_rules *rules);
void					get_philo_ready(t_rules *rules, int idx);
void					the_philosopher(t_rules *rules, int idx);
void					philo_printer(t_rules *rules, const char *msg);
void					death_printer(t_rules *rules, const char *msg);
void					rules_setting(t_rules **rules, int argc, char **argv);
bool					sleep_awake(t_rules *rules, long start, long to_sleep);

#endif