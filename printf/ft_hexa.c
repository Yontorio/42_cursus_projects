/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:00:50 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/01 18:12:44 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_calculate_zero_length(unsigned int n, struct s_flags flag)
{
	int	num_len;

	num_len = ft_calculate_length_hex(n, &flag);
	if (flag.precision > num_len)
		return (flag.precision - num_len);
	else
		return (0);
}

static void	ft_print_hash_prefix(unsigned int n, int uppercase,
		struct s_flags flag)
{
	if (flag.hash && n != 0)
	{
		if (uppercase)
			write(1, "0X", 2);
		else
			write(1, "0x", 2);
	}
}

static void	ft_pad_with_spaces(int tot_len, int flag_width, int *num_len,
		struct s_flags flag)
{
	while (tot_len < flag_width)
	{
		if (flag.zero && !(flag.isprecision))
			ft_putchar('0');
		else
			ft_putchar(' ');
		tot_len++;
		(*num_len)++;
	}
}

static int	ft_not_minus(unsigned int n, int uppercase, struct s_flags flag)
{
	int	num_len;
	int	zero_len;
	int	tot_len;

	num_len = 0;
	zero_len = 0;
	tot_len = 0;
	tot_len = ft_calculate_total_length(n, flag);
	zero_len = ft_calculate_zero_length(n, flag);
	ft_print_hash_prefix(n, uppercase, flag);
	ft_pad_with_spaces(tot_len, flag.width, &num_len, flag);
	while (zero_len > 0)
	{
		ft_putchar('0');
		zero_len--;
		num_len++;
	}
	return (num_len);
}

int	ft_hexa(unsigned int n, int uppercase, struct s_flags flag)
{
	int	num_len;

	num_len = 0;
	if (!flag.zero && !flag.iswidth && !flag.isprecision)
		num_len += ft_puthex(n, uppercase, flag);
	else if (flag.minus)
		num_len = ft_minus_hex(n, uppercase, flag);
	else
	{
		num_len = ft_not_minus(n, uppercase, flag);
		if (n != 0 || !flag.isprecision)
			num_len += ft_puthex(n, uppercase, flag);
	}
	return (num_len);
}
