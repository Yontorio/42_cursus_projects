/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:57:39 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/07 00:14:05 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned int n, struct s_flags flag)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_putunsigned(n / 10, flag);
	count += ft_putchar((n % 10) + '0');
	return (count);
}

static int	ft_minus(unsigned int n, struct s_flags flag)
{
	int	num_len;

	num_len = ft_unsigned_len(n);
	if (n == 0 && flag.isprecision)
		num_len = 0;
	while (num_len < flag.precision)
	{
		ft_putchar('0');
		num_len++;
	}
	if (n != 0 || !flag.isprecision)
		ft_putunsigned(n, flag);
	while (num_len < flag.width)
	{
		ft_putchar(' ');
		num_len++;
	}
	return (num_len);
}

static void	ft_print_padding_and_zeros(struct s_flags flag, int *tot_len,
		int *num_len, int zero_len)
{
	while (*tot_len < flag.width)
	{
		if (flag.zero && !(flag.isprecision))
			ft_putchar('0');
		else
			ft_putchar(' ');
		(*tot_len)++;
		(*num_len)++;
	}
	while (zero_len > 0)
	{
		ft_putchar('0');
		zero_len--;
		(*num_len)++;
	}
}

static int	ft_minus_not(int n, struct s_flags flag, int zero_len, int tot_len)
{
	int	num_len;

	num_len = ft_unsigned_len(n);
	if (n == 0 && flag.isprecision)
		num_len = 0;
	if (flag.precision > num_len)
		tot_len = flag.precision;
	else
		tot_len = num_len;
	zero_len = flag.precision - num_len;
	ft_print_padding_and_zeros(flag, &tot_len, &num_len, zero_len);
	return (num_len);
}

int	ft_unsigned(unsigned int n, struct s_flags flag)
{
	int	num_len;
	int	zero_len;
	int	tot_len;

	zero_len = 0;
	tot_len = 0;
	num_len = 0;
	if (!flag.zero && !flag.iswidth && !flag.isprecision)
		num_len += ft_putunsigned(n, flag);
	else if (flag.minus)
		num_len = ft_minus(n, flag);
	else
	{
		num_len = ft_minus_not(n, flag, zero_len, tot_len);
		if (n != 0 || !flag.isprecision)
			ft_putunsigned(n, flag);
	}
	return (num_len);
}
