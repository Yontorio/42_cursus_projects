/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:04:26 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/07 00:25:28 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_calculate_tot_len(int n, struct s_flags flag)
{
	int	num_len;
	int	tot_len;

	num_len = ft_calculate_length_int(n, &flag);
	if (flag.isprecision && flag.precision > num_len)
		tot_len = flag.precision;
	else
		tot_len = num_len;
	if (flag.sign)
		tot_len += 1;
	if (flag.plus)
		tot_len += 1;
	if (flag.space && !flag.isprecision && flag.iswidth && flag.zero)
		tot_len += 1;
	return (tot_len);
}

static int	ft_25_line(int n, struct s_flags flag)
{
	int	count;

	count = 0;
	if (flag.sign && flag.zero && !flag.isprecision)
		count += ft_putchar('-');
	if (n >= 0 && flag.space && !flag.isprecision && (flag.iswidth
			&& flag.zero))
		count += ft_putchar(' ');
	if (n >= 0 && flag.plus && !flag.isprecision && flag.zero)
		count += ft_putchar('+');
	return (count);
}

static int	ft_pad_with_spaces_or_zeros(int n, int *tot_len, int *num_len,
		struct s_flags flag)
{
	int	count;

	count = 0;
	count += ft_25_line(n, flag);
	while (*tot_len < flag.width)
	{
		if (flag.zero && !flag.isprecision)
			ft_putchar('0');
		else
			ft_putchar(' ');
		(*tot_len)++;
		(*num_len)++;
	}
	if (flag.sign && (!flag.zero || (flag.zero && flag.isprecision)))
		count += ft_putchar('-');
	if (n >= 0 && flag.space && flag.isprecision && (!flag.iswidth
			&& !flag.zero))
		count += ft_putchar(' ');
	if (n >= 0 && flag.plus && flag.isprecision)
		count += ft_putchar('+');
	return (count);
}

static int	ft_minus_not(int n, struct s_flags flag)
{
	int	num_len;
	int	zero_len;
	int	tot_len;
	int	count;

	num_len = 0;
	zero_len = 0;
	tot_len = 0;
	count = 0;
	num_len = ft_calculate_length_int(n, &flag);
	tot_len = ft_calculate_tot_len(n, flag);
	if (flag.precision - num_len > 0)
		zero_len = flag.precision - num_len;
	else
		zero_len = 0;
	count += ft_pad_with_spaces_or_zeros(n, &tot_len, &num_len, flag);
	while (flag.isprecision && zero_len > 0)
	{
		ft_putchar('0');
		zero_len--;
		num_len++;
	}
	num_len += count;
	return (num_len);
}

int	ft_integer(int n, struct s_flags flag)
{
	int	num_len;

	num_len = 0;
	if (!flag.zero && !flag.iswidth && !flag.isprecision)
		num_len += ft_putnbr(n, flag);
	else if (flag.minus)
		num_len = ft_minus_int(n, flag);
	else
	{
		num_len = ft_minus_not(n, flag);
		ft_putnbr(n, flag);
	}
	return (num_len);
}
