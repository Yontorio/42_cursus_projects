/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_familly.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:10:15 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/21 03:25:42 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min(t_list *stack)
{
	int	min;

	if (!stack)
		return (INT_MAX);
	min = stack->element;
	while (stack)
	{
		if (stack->element < min)
			min = stack->element;
		stack = stack->next;
	}
	return (min);
}

int	find_max(t_list *stack)
{
	int	max;

	if (!stack)
		return (INT_MIN);
	max = stack->element;
	while (stack)
	{
		if (stack->element > max)
			max = stack->element;
		stack = stack->next;
	}
	return (max);
}

int	find_index_of_value(t_list *stack, int value)
{
	int	index;

	index = 0;
	while (stack)
	{
		if (stack->element == value)
			return (index);
		index++;
		stack = stack->next;
	}
	return (INT_MIN);
}

t_list	*find_best_candidate(t_list *a)
{
	t_list	*best;
	t_list	*curr;

	if (!a)
		return (NULL);
	best = a;
	curr = best;
	while (curr)
	{
		if (curr->total_cost < best->total_cost)
			best = curr;
		else if (curr->total_cost == best->total_cost)
		{
			if (curr->element > best->element)
				best = curr;
		}
		curr = curr->next;
	}
	return (best);
}
