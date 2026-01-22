/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:55:06 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/19 01:55:07 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_list **list)
{
	t_list	*first_node;
	t_list	*last_node;

	if (list == NULL || *list == NULL || (*list)->next == NULL)
		return ;
	first_node = *list;
	last_node = get_last_node(*list);
	*list = first_node->next;
	(*list)->prev = NULL;
	first_node->next = NULL;
	first_node->prev = last_node;
	last_node->next = first_node;
	return ;
}

void	ra(t_list **a, int flag)
{
	rotate(a);
	if (!flag)
		write(1, "ra\n", 3);
}

void	rb(t_list **b, int flag)
{
	rotate(b);
	if (!flag)
		write(1, "rb\n", 3);
}

void	rr(t_list **a, t_list **b, int flag)
{
	rotate(a);
	rotate(b);
	if (!flag)
		write(1, "rr\n", 3);
}
