/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:15:36 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/23 02:10:33 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	kill_check(pid_t pid, int signum)
{
	if (kill(pid, signum) < 0)
	{
		write(1, "error\n", 7);
		return ;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	digit;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	digit = (nb % 10) + '0';
	write(fd, &digit, 1);
}

int	is_valid_pid_str(const char *str)
{
	const char	*ptr = str;

	if (!str || *str == '\0')
		return (0);
	while (*ptr)
	{
		if (*ptr < '0' || *ptr > '9')
			return (0);
		ptr++;
	}
	return (1);
}

pid_t	atopid(const char *str)
{
	unsigned long	result;
	const char		*ptr = str;
	int				digit;

	result = 0;
	if (!is_valid_pid_str(str))
		return (-1);
	while (*ptr)
	{
		digit = *ptr - '0';
		if (result > (UINT_MAX / 10) || (result == (UINT_MAX / 10)
				&& (unsigned long)digit > (UINT_MAX % 10)))
		{
			return (-1);
		}
		result = result * 10 + (unsigned long)digit;
		ptr++;
	}
	if (result == 0 || result > PID_MAX_LIMIT)
		return (-1);
	return ((pid_t)result);
}
