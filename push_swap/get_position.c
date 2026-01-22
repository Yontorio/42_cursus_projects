/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:10:45 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/19 02:22:27 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	update_best_value(int *best_idx, int *best_val, int element,
		int idx)
{
	*best_val = element;
	*best_idx = idx;
	return (1);
}

static int	get_fallback_index(t_list *b, int found, int best_idx, int fallback)
{
	if (!found)
		return (find_index_of_value(b, fallback));
	return (best_idx);
}

int	get_descending_position(t_list *b, int value)
{
	int		best_idx;
	int		best_val;
	t_list	*curr;
	int		idx;
	int		found;

	if (list_size(b) == 0)
		return (0);
	best_idx = 0;
	best_val = INT_MAX;
	curr = b;
	idx = 0;
	found = 0;
	while (curr)
	{
		if (curr->element < value)
		{
			if (!found || curr->element > best_val)
				found = update_best_value(&best_idx, &best_val, curr->element,
						idx);
		}
		idx++;
		curr = curr->next;
	}
	return (get_fallback_index(b, found, best_idx, find_max(b)));
}

int	get_ascending_position(t_list *b, int value)
{
	int		best_idx;
	int		best_val;
	t_list	*curr;
	int		idx;
	int		found;

	if (list_size(b) == 0)
		return (0);
	best_idx = 0;
	best_val = INT_MAX;
	curr = b;
	idx = 0;
	found = 0;
	while (curr)
	{
		if (curr->element > value)
		{
			if (!found || curr->element < best_val)
				found = update_best_value(&best_idx, &best_val, curr->element,
						idx);
		}
		idx++;
		curr = curr->next;
	}
	return (get_fallback_index(b, found, best_idx, find_min(b)));
}
