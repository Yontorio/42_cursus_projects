/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:48:40 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/20 20:14:00 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_isdigit(int c)
{
	return ('0' <= c && '9' >= c);
}

int	only_digits(char *s)
{
	size_t	i;

	i = 0;
	if ((s[i] == '-' || s[i] == '+') && s[i + 1])
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	clear(char **vector, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(vector[i]);
		i++;
	}
	free(vector);
}

int	duplicates(t_list *stack, int number)
{
	t_list	*current;

	current = stack;
	while (current)
	{
		if (current->element == number)
			return (1);
		current = current->next;
	}
	return (0);
}
