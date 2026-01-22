/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:50:03 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/18 21:50:04 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_list *stack, int order)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (order == ASCENDING)
		{
			if (stack->element > stack->next->element)
				return (0);
		}
		else if (order == DESCENDING)
		{
			if (stack->element < stack->next->element)
				return (0);
		}
		stack = stack->next;
	}
	return (1);
}
