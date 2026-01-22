/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:16:47 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/23 07:06:26 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	process_signal_bit(int sig, char *c, int *bit)
{
	if (sig == SIGUSR1)
		*c |= (0b10000000 >> *bit);
	else if (sig == SIGUSR2)
		*c &= ~(0b10000000 >> *bit);
	(*bit)++;
}

static int	handle_complete_char(pid_t sender, char *c, int *bit)
{
	if (*bit == __CHAR_BIT__)
	{
		*bit = 0;
		if (*c == '\0')
		{
			*c = 0;
			write(STDOUT_FILENO, "\n", 1);
			kill_check(sender, SIGUSR2);
			return (0);
		}
		write(STDOUT_FILENO, c, 1);
		*c = 0;
	}
	return (1);
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		bit = 0;
	static pid_t	sender = 0;

	(void)context;
	if (info->si_pid)
	{
		if (sender != info->si_pid)
		{
			c = 0;
			bit = 0;
		}
		sender = info->si_pid;
	}
	process_signal_bit(sig, &c, &bit);
	if (handle_complete_char(sender, &c, &bit))
		kill_check(sender, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
