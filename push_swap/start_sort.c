/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:50:36 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/19 02:21:51 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	push_swap_check(t_list **a)
{
	int	sorted;
	int	size_a;

	sorted = is_sorted(*a, ASCENDING);
	size_a = list_size(*a);
	if (sorted)
		return (1);
	else if (size_a == 2 && !sorted)
		return (sa(a, NO_CHECKER), 1);
	else if (size_a == 3 && !sorted)
		return (sort_a(a), 1);
	else
		return (0);
}

void	push_swap(t_list **a, t_list **b)
{
	if (push_swap_check(a))
		return ;
	while (list_size(*a) > 3 && list_size(*b) < 3)
	{
		pb(a, b, NO_CHECKER);
		if ((list_size(*a) == 3 || is_sorted(*a, ASCENDING))
			&& list_size(*b) == 1)
			return (sort_a(a), push_back(a, b));
		if ((list_size(*a) == 3 || is_sorted(*a, ASCENDING))
			&& list_size(*b) > 1)
			return (sort_a(a), sort_b(b), push_back(a, b));
	}
	sort_b(b);
	while (list_size(*a) > 3)
	{
		update_infos(*a, *b);
		execute_rotations(a, b, find_best_candidate(*a));
		pb(a, b, NO_CHECKER);
	}
	sort_a(a);
	push_back(a, b);
}
