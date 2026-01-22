/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:55:22 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/19 01:56:31 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_a(t_list **list)
{
	int	min_a;

	if (is_sorted(*list, ASCENDING))
		return ;
	min_a = find_max(*list);
	if ((*list)->element != min_a && get_last_node(*list)->element != min_a)
		rra(list, NO_CHECKER);
	else if ((*list)->element == min_a)
		ra(list, NO_CHECKER);
	if ((*list)->element > (*list)->next->element)
		sa(list, NO_CHECKER);
}

void	sort_b(t_list **list)
{
	int	min_b;

	if (is_sorted(*list, DESCENDING))
		return ;
	min_b = find_min(*list);
	if ((*list)->element != min_b && get_last_node(*list)->element != min_b)
		rrb(list, NO_CHECKER);
	else if ((*list)->element == min_b)
		rb(list, NO_CHECKER);
	if ((*list)->element < (*list)->next->element)
		sb(list, NO_CHECKER);
}
