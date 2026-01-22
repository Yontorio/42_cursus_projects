/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:54:37 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/19 01:54:38 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_list **src, t_list **dst)
{
	t_list	*node;

	if (*src == NULL)
		return ;
	node = *src;
	*src = node->next;
	if (*src)
		(*src)->prev = NULL;
	node->next = *dst;
	if (*dst)
		(*dst)->prev = node;
	node->prev = NULL;
	*dst = node;
}

void	pa(t_list **a, t_list **b, int flag)
{
	push(b, a);
	if (!flag)
		write(1, "pa\n", 3);
}

void	pb(t_list **a, t_list **b, int flag)
{
	push(a, b);
	if (!flag)
		write(1, "pb\n", 3);
}
