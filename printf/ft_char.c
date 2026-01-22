/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:57:30 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/07 00:23:03 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static void	ft_width(int *num_len, struct s_flags *flag)
{
	while (flag->iswidth && *num_len < flag->width)
	{
		ft_putchar(' ');
		(*num_len)++;
	}
}

int	ft_char(char s, struct s_flags flag)
{
	int	num_len;

	num_len = 1;
	if (!flag.iswidth && !flag.isprecision)
	{
		ft_putchar(s);
		return (num_len);
	}
	if (flag.minus)
	{
		ft_putchar(s);
		ft_width(&num_len, &flag);
	}
	else
	{
		ft_width(&num_len, &flag);
		ft_putchar(s);
	}
	return (num_len);
}

int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}
