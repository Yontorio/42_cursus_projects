/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:15:24 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/23 02:08:14 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_acknowledgement = WAIT;

static void	exit_sig(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nmessage sent successfully\n", 28);
	exit(EXIT_SUCCESS);
}

static void	acknowledge(int sig)
{
	(void)sig;
	g_acknowledgement = RECEIVED;
}

static void	send_char(char c, pid_t server)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (c & (0b10000000 >> bit))
			kill(server, SIGUSR1);
		else
			kill(server, SIGUSR2);
		bit++;
		while (g_acknowledgement == WAIT)
			usleep(20);
		g_acknowledgement = WAIT;
	}
}

static void	send_message(const char *message, pid_t server)
{
	int	i;

	i = 0;
	while (message[i])
		send_char(message[i++], server);
	send_char('\0', server);
}

int	main(int ac, char **av)
{
	pid_t	server;

	if (ac != 3)
	{
		write(1, "error\n", 7);
		return (EXIT_FAILURE);
	}
	server = get_server_pid(av[1]);
	check_server_pid(server);
	signal_handler(SIGUSR1, acknowledge);
	signal_handler(SIGUSR2, exit_sig);
	send_message(av[2], server);
	return (EXIT_SUCCESS);
}
