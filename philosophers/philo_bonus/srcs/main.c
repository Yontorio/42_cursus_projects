/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:47 by ahoummad          #+#    #+#             */
/*   Updated: 2025/07/31 07:25:51 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;

	rules = NULL;
	rules_setting(&rules, argc, argv);
	if (rules->num_of_philos == ONE_GUEST)
		one_guest(rules);
	prepare_table(rules);
	begin_simulation(rules);
	return (EXIT_SUCCESS);
}
