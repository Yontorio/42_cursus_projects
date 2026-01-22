/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 09:41:15 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/23 09:41:16 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# define PID_MAX_LIMIT 4194304

# define RECEIVED 1
# define WAIT 0

void	ft_putnbr_fd(int n, int fd);
pid_t	atopid(const char *str);
void	kill_check(pid_t pid, int signum);
void	signal_handler(int sig, void *handler);
void	check_server_pid(pid_t server);
pid_t	get_server_pid(char *pid_str);

#endif