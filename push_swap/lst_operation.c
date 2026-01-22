/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:46:56 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/19 02:22:17 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*get_last_node(t_list *head)
{
	t_list	*current;

	if (head == NULL)
		return (NULL);
	current = head;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

int	list_size(t_list *head)
{
	int		size;
	t_list	*current;

	size = 0;
	current = head;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

void	free_list(t_list *head)
{
	t_list	*current;
	t_list	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
}

static int	append_number(t_list **stack, int num)
{
	t_list	*node;
	t_list	*last;

	node = malloc(sizeof(t_list));
	if (!node)
		return (1);
	node->element = num;
	node->next = NULL;
	if (!*stack)
	{
		node->prev = NULL;
		*stack = node;
	}
	else
	{
		last = get_last_node(*stack);
		last->next = node;
		node->prev = last;
	}
	return (0);
}

t_list	*create_stack(int ac, char **av)
{
	t_list	*stack;
	long	number;
	int		i;

	stack = NULL;
	i = 0;
	while (i < ac)
	{
		number = ft_atol(av[i]);
		if (number > INT_MAX || number < INT_MIN || !only_digits(av[i])
			|| !ft_strlen(av[i]) || duplicates(stack, number))
			return (free_list(stack), NULL);
		if (append_number(&stack, (int)number))
			return (free_list(stack), NULL);
		i++;
	}
	return (stack);
}
