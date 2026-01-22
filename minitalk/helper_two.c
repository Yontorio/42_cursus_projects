/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:15:44 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/23 09:40:59 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig, void *handler)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(sig, &sa, NULL) < 0)
		exit(EXIT_FAILURE);
}

void	check_server_pid(pid_t server)
{
	if (kill(server, 0) == -1)
	{
		if (errno == ESRCH)
			write(STDERR_FILENO, "Error: Server PID does not exist\n", 33);
		else if (errno == EPERM)
			write(STDERR_FILENO, "Error: Permission denied\n", 25);
		exit(EXIT_FAILURE);
	}
}

pid_t	get_server_pid(char *pid_str)
{
	pid_t	server;

	server = atopid(pid_str);
	if (server == -1)
	{
		write(1, "Invalid PID\n", 13);
		exit(EXIT_FAILURE);
	}
	return (server);
}
