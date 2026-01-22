/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:26:20 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/23 09:06:11 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	copy = malloc(i + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	ft_lstclean_up(struct s_list_gnl **list, struct s_list_gnl *new_node,
		char *new_data)
{
	struct s_list_gnl	*tmp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->data);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (new_node->data[0])
		*list = new_node;
	else
	{
		free(new_data);
		free(new_node);
	}
}

struct s_list_gnl	*ft_lstnew(char *data)
{
	struct s_list_gnl	*new_node;

	new_node = (struct s_list_gnl *)malloc(sizeof(struct s_list_gnl));
	if (!new_node)
		return (NULL);
	new_node->data = ft_strdup(data);
	if (!new_node->data)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(struct s_list_gnl **lst, struct s_list_gnl *new)
{
	struct s_list_gnl	*current;

	if (!*lst)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

char	*found_newline(struct s_list_gnl *list)
{
	struct s_list_gnl	*current;
	char				*ptr;

	current = list;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	if (!current->data)
		return (NULL);
	ptr = current->data;
	while (*ptr != '\0')
	{
		if (*ptr == '\n')
			return (ptr);
		ptr++;
	}
	return (NULL);
}
