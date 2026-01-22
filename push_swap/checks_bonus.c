/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:05:39 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/23 09:05:40 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	no_match(t_list **a, t_list **b, char *move)
{
	free(move);
	free_list(*a);
	free_list(*b);
	write(2, "Error\n", 6);
	exit(1);
}

static void	push_check(t_list **a, t_list **b, char *move)
{
	size_t	len;

	len = ft_strlen(move);
	if (!ft_strncmp(move, "pa\n", len))
		pa(a, b, CHECKER);
	else if (!ft_strncmp(move, "pb\n", len))
		pb(a, b, CHECKER);
	else
		no_match(a, b, move);
}

static void	swap_check(t_list **a, t_list **b, char *move)
{
	size_t	len;

	len = ft_strlen(move);
	if (!ft_strncmp(move, "sa\n", len))
		sa(a, CHECKER);
	else if (!ft_strncmp(move, "sb\n", len))
		sb(b, CHECKER);
	else if (!ft_strncmp(move, "ss\n", len))
		ss(a, b, CHECKER);
	else
		no_match(a, b, move);
}

static void	rot_rev_check(t_list **a, t_list **b, char *move)
{
	size_t	len;

	len = ft_strlen(move);
	if (!ft_strncmp(move, "ra\n", len))
		ra(a, CHECKER);
	else if (!ft_strncmp(move, "rb\n", len))
		rb(b, CHECKER);
	else if (!ft_strncmp(move, "rr\n", len))
		rr(a, b, CHECKER);
	else if (!ft_strncmp(move, "rra\n", len))
		rra(a, CHECKER);
	else if (!ft_strncmp(move, "rrb\n", len))
		rrb(b, CHECKER);
	else if (!ft_strncmp(move, "rrr\n", len))
		rrr(a, b, CHECKER);
	else
		no_match(a, b, move);
}

void	moves_check(t_list **a, t_list **b, char *move)
{
	if (move[0] == 'p')
		push_check(a, b, move);
	else if (move[0] == 's')
		swap_check(a, b, move);
	else if (move[0] == 'r')
		rot_rev_check(a, b, move);
	else
		no_match(a, b, move);
}
