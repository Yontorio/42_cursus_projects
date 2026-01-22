/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:05:34 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/23 09:03:11 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "push_swap.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

struct					s_list_gnl
{
	char				*data;
	struct s_list_gnl	*next;
};

void					moves_check(t_list **a, t_list **b, char *move);
struct s_list_gnl		*ft_lstnew(char *data);
void					ft_lstclean_up(struct s_list_gnl **list,
							struct s_list_gnl *new_node, char *new_data);
void					ft_lstadd_back(struct s_list_gnl **lst,
							struct s_list_gnl *new);
char					*ft_strdup(const char *s);
char					*found_newline(struct s_list_gnl *list);
void					add_line_to_list(struct s_list_gnl **list, int fd);
char					*construct_line(struct s_list_gnl *list);
int						get_line_length(struct s_list_gnl *list);
void					next_line(struct s_list_gnl **list);
char					*get_next_line(int fd);

#endif