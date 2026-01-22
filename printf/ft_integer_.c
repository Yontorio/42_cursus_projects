/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:04:35 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/07 00:24:54 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_minus_int(int n, struct s_flags flag)
{
	int	num_len;

	num_len = ft_calculate_length_int(n, &flag);
	if (flag.sign)
		ft_putchar('-');
	if (n >= 0 && flag.plus)
		ft_putchar('+');
	if (n >= 0 && flag.space)
		ft_putchar(' ');
	while (flag.isprecision && num_len < flag.precision)
	{
		ft_putchar('0');
		num_len++;
	}
	ft_putnbr(n, flag);
	if (flag.sign || (n >= 0 && flag.plus) || (n >= 0 && flag.space))
		num_len += 1;
	while (flag.iswidth && num_len < flag.width)
	{
		ft_putchar(' ');
		num_len++;
	}
	return (num_len);
}

int	ft_calculate_length_int(int n, struct s_flags *flag)
{
	int	num_len;

	num_len = ft_numlen(n);
	if (n < 0)
		flag->sign = 1;
	if (n == 0 && flag->isprecision)
		num_len = 0;
	return (num_len);
}

int	ft_process_sign_and_flags(int *n, struct s_flags *flag)
{
	int	count;

	count = 0;
	if (*n >= 0 && flag->space && !flag->iswidth && !flag->isprecision
		&& !flag->zero)
		count += ft_putchar(' ');
	flag->space = 0;
	if (*n >= 0 && flag->plus && !flag->iswidth && !flag->isprecision
		&& !flag->zero)
	{
		count += ft_putchar('+');
		flag->plus = 0;
	}
	if (*n < 0)
	{
		if (!flag->zero && !flag->iswidth && !flag->isprecision)
			count += ft_putchar('-');
		*n = -(*n);
	}
	return (count);
}

int	ft_recursive_putnbr(int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_recursive_putnbr(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}

int	ft_putnbr(int n, struct s_flags flag)
{
	int	count;

	count = 0;
	count += ft_process_sign_and_flags(&n, &flag);
	if (n == -2147483648)
	{
		count += ft_putchar('2');
		count += ft_recursive_putnbr(147483648);
		return (count);
	}
	if (n == 0 && flag.isprecision)
		return (count);
	count += ft_recursive_putnbr(n);
	return (count);
}
