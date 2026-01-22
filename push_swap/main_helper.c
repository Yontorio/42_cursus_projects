/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:06:11 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/20 20:19:43 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

static int	get_words(int ac, char **av)
{
	int	wc;
	int	i;

	wc = 0;
	i = 0;
	while (i < ac)
	{
		if (ft_strlen(av[i]) == 0)
			return (-1);
		wc += count_words(av[i], ' ');
		i++;
	}
	return (wc);
}

static int	split_numbers(char **args, int ac, char **av)
{
	char	**words;
	int		wc;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < ac)
	{
		j = 0;
		words = ft_split(av[i], ' ');
		wc = count_words(av[i], ' ');
		if (!words || !wc)
			return (clear(args, k), free(words), 1);
		while (j < wc)
			args[k++] = words[j++];
		i++;
		free(words);
	}
	return (args[k] = NULL, 0);
}

t_list	*get_arguments(int ac, char **av)
{
	int		argc;
	char	**args;
	t_list	*nums;

	argc = get_words(ac, av);
	if (argc < 0)
		return (NULL);
	args = malloc((argc + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	if (split_numbers(args, ac, av) == 1)
		return (NULL);
	nums = create_stack(argc, args);
	clear(args, argc);
	if (!nums)
		return (NULL);
	return (nums);
}
