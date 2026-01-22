/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:54:53 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/19 01:54:54 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_list **list)
{
	t_list	*node;

	if (list == NULL || *list == NULL || (*list)->next == NULL)
		return ;
	node = get_last_node(*list);
	node->prev->next = NULL;
	node->prev = NULL;
	node->next = *list;
	(*list)->prev = node;
	*list = node;
	return ;
}

void	rra(t_list **a, int flag)
{
	reverse_rotate(a);
	if (!flag)
		write(1, "rra\n", 4);
}

void	rrb(t_list **b, int flag)
{
	reverse_rotate(b);
	if (!flag)
		write(1, "rrb\n", 4);
}

void	rrr(t_list **a, t_list **b, int flag)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (!flag)
		write(1, "rrr\n", 4);
}
