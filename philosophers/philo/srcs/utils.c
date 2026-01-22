/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:04:22 by ahoummad          #+#    #+#             */
/*   Updated: 2025/08/04 09:11:34 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p)
		++p;
	return (p - s);
}

static int	overflow(long result, int sign)
{
	if (sign == 1 && result > (long)INT_MAX)
		return (1);
	if (sign == -1 && result > (long)INT_MIN)
		return (1);
	return (0);
}

int	ato_rule(char *s)
{
	long	result;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	result = 0;
	if (!s)
		return (-1);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign = -1;
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i++] - '0');
		if (overflow(result, sign))
			return (-1);
	}
	return ((int)(result * sign));
}

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	sleep_awake(t_philo *philo, long start, long to_sleep)
{
	while (death_check(philo))
	{
		if (to_sleep <= (current_time() - start))
			return (true);
		usleep(CHECK_PRECISION);
	}
	return (false);
}
