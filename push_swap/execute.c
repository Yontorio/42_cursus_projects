/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:51:15 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/20 20:12:26 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	simultaneous_rotations(t_list **a, t_list **b, t_list *candidate)
{
	while (candidate->cost_a > 0 && candidate->cost_b > 0
		&& candidate->direction_a == candidate->direction_b)
	{
		if (candidate->direction_a == 1)
			rr(a, b, NO_CHECKER);
		else
			rrr(a, b, NO_CHECKER);
		candidate->cost_a--;
		candidate->cost_b--;
	}
}

void	execute_rotations(t_list **a, t_list **b, t_list *candidate)
{
	simultaneous_rotations(a, b, candidate);
	while (candidate->cost_a > 0)
	{
		if (candidate->direction_a == 1)
			ra(a, NO_CHECKER);
		else
			rra(a, NO_CHECKER);
		candidate->cost_a--;
	}
	while (candidate->cost_b > 0)
	{
		if (candidate->direction_b == 1)
			rb(b, NO_CHECKER);
		else
			rrb(b, NO_CHECKER);
		candidate->cost_b--;
	}
}
