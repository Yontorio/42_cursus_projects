/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:05:30 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/23 09:05:48 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	checker(t_list **a, t_list **b)
{
	int		size_a;
	char	*line;

	size_a = list_size(*a);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		moves_check(a, b, line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (is_sorted(*a, ASCENDING) && list_size(*a) == size_a)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

int	main(int argc, char *argv[])
{
	t_list	*a;
	t_list	*b;

	if (argc < 2)
		return (0);
	a = get_arguments(argc - 1, argv + 1);
	b = NULL;
	if (!a)
		error();
	checker(&a, &b);
	free_list(a);
	free_list(b);
	return (0);
}
