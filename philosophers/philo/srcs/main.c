/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:10 by ahoummad          #+#    #+#             */
/*   Updated: 2025/07/31 07:04:11 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;

	rules = NULL;
	if (rules_setting(&rules, argc, argv))
		return (EXIT_FAILURE);
	if (rules->num_of_philos == ONE_GUEST)
		return (one_guest(rules));
	if (prepare_table(rules))
		return (EXIT_FAILURE);
	if (seat_philos(rules))
		return (EXIT_FAILURE);
	return (begin_simulation(rules));
}
