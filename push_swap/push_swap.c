/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:49:14 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/20 20:21:24 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	push_swap(&a, &b);
	free_list(a);
	free_list(b);
	return (0);
}
