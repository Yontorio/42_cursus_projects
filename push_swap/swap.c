/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:56:39 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/19 01:56:56 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_list **list)
{
	t_list	*first;
	t_list	*second;

	if (list == NULL || *list == NULL || (*list)->next == NULL)
		return ;
	first = *list;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	*list = second;
}

void	sa(t_list **a, int flag)
{
	swap(a);
	if (!flag)
		write(1, "sa\n", 3);
}

void	sb(t_list **b, int flag)
{
	swap(b);
	if (!flag)
		write(1, "sb\n", 3);
}

void	ss(t_list **a, t_list **b, int flag)
{
	swap(a);
	swap(b);
	if (!flag)
		write(1, "ss\n", 3);
}
