/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:06:21 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/20 20:10:55 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# define CHECKER 1
# define NO_CHECKER 0
# define ASCENDING 1
# define DESCENDING 0

typedef struct s_list
{
	int				element;
	struct s_list	*prev;
	struct s_list	*next;
	int				position;
	int				cost_a;
	int				cost_b;
	int				total_cost;
	int				direction_a;
	int				direction_b;
	int				insert_position;
}					t_list;

void				push_swap(t_list **a, t_list **b);
char				**ft_split(char const *s, char c);
long				ft_atol(char *str);
t_list				*get_last_node(t_list *head);
void				free_list(t_list *head);
int					list_size(t_list *head);
int					is_sorted(t_list *stack, int order);
void				sort_a(t_list **list);
void				sort_b(t_list **list);
void				adjust_stack_a(t_list **a);
void				push_back(t_list **a, t_list **b);
int					find_min(t_list *stack);
int					find_max(t_list *stack);
int					find_index_of_value(t_list *stack, int value);
t_list				*find_best_candidate(t_list *a);
int					get_descending_position(t_list *b, int value);
int					get_ascending_position(t_list *b, int value);
void				update_infos(t_list *a, t_list *b);
void				execute_rotations(t_list **a, t_list **b,
						t_list *candidate);
int					only_digits(char *s);
int					duplicates(t_list *stack, int number);
size_t				ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_isspace(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				error(void);
int					count_words(char const *str, char c);
void				clear(char **vector, int count);
t_list				*create_stack(int ac, char **av);
t_list				*get_arguments(int ac, char **av);

void				sa(t_list **a, int flag);
void				sb(t_list **b, int flag);
void				ss(t_list **a, t_list **b, int flag);
void				ra(t_list **a, int flag);
void				rb(t_list **b, int flag);
void				rr(t_list **a, t_list **b, int flag);
void				rra(t_list **a, int flag);
void				rrb(t_list **b, int flag);
void				rrr(t_list **a, t_list **b, int flag);
void				pa(t_list **a, t_list **b, int flag);
void				pb(t_list **b, t_list **a, int flag);

#endif
