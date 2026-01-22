/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:54:23 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/19 02:22:42 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	adjust_stack_a(t_list **a)
{
	int	size;
	int	min;
	int	index;
	int	i;

	i = 0;
	size = list_size(*a);
	min = find_min(*a);
	index = find_index_of_value(*a, min);
	if (index <= size / 2)
	{
		while (i++ < index)
			ra(a, NO_CHECKER);
	}
	else
	{
		while (i++ < size - index)
			rra(a, NO_CHECKER);
	}
}

void	push_back(t_list **a, t_list **b)
{
	int	i;
	int	size;
	int	target_index;

	while (*b)
	{
		i = 0;
		size = list_size(*a);
		target_index = get_ascending_position(*a, (*b)->element);
		if (target_index <= size / 2)
		{
			while (i++ < target_index)
				ra(a, NO_CHECKER);
		}
		else
		{
			while (i++ < size - target_index)
				rra(a, NO_CHECKER);
		}
		pa(a, b, NO_CHECKER);
	}
	adjust_stack_a(a);
}
