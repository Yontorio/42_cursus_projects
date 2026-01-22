/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:53:40 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/20 20:12:26 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	update_cost_a(t_list *node, int index, int size_a)
{
	node->position = index;
	if (index <= size_a / 2)
	{
		node->cost_a = index;
		node->direction_a = 1;
	}
	else
	{
		node->cost_a = size_a - index;
		node->direction_a = -1;
	}
}

static void	update_cost_b(t_list *node, int size_b, t_list *b)
{
	node->insert_position = get_descending_position(b, node->element);
	if (size_b == 0)
	{
		node->cost_b = 0;
		node->direction_b = 0;
	}
	else if (node->insert_position <= size_b / 2)
	{
		node->cost_b = node->insert_position;
		node->direction_b = 1;
	}
	else
	{
		node->cost_b = size_b - node->insert_position;
		node->direction_b = -1;
	}
}

static void	update_total_cost(t_list *node)
{
	if (node->direction_a == node->direction_b)
	{
		if (node->cost_a > node->cost_b)
			node->total_cost = node->cost_a;
		else
			node->total_cost = node->cost_b;
	}
	else
	{
		node->total_cost = node->cost_a + node->cost_b;
	}
}

void	update_infos(t_list *a, t_list *b)
{
	int		index;
	t_list	*curr;

	index = 0;
	curr = a;
	while (curr)
	{
		update_cost_a(curr, index, list_size(a));
		update_cost_b(curr, list_size(b), b);
		update_total_cost(curr);
		index++;
		curr = curr->next;
	}
}
