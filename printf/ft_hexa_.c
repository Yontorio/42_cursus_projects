/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:04:28 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/01 18:12:07 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_len(unsigned int num)
{
	int	len;

	len = 0;
	if (num == 0)
	{
		return (1);
	}
	while (num != 0)
	{
		len++;
		num /= 16;
	}
	return (len);
}

int	ft_calculate_length_hex(unsigned int n, struct s_flags *flag)
{
	int	num_len;

	num_len = ft_hex_len(n);
	if (flag->hash)
		flag->width -= 2;
	if (n == 0 && flag->isprecision)
		num_len = 0;
	return (num_len);
}

int	ft_puthex(unsigned int n, int uppercase, struct s_flags flag)
{
	int	count;

	count = 0;
	if (flag.hash && !flag.zero && !flag.isprecision && !flag.iswidth && n != 0)
	{
		if (uppercase)
			count += write(1, "0X", 2);
		else
			count += write(1, "0x", 2);
		flag.hash = 0;
	}
	if (n >= 16)
		count += ft_puthex(n / 16, uppercase, flag);
	if (n % 16 < 10)
		count += ft_putchar((n % 16) + '0');
	else
	{
		if (uppercase)
			count += ft_putchar((n % 16) - 10 + 'A');
		else
			count += ft_putchar((n % 16) - 10 + 'a');
	}
	return (count);
}

int	ft_minus_hex(unsigned int n, int uppercase, struct s_flags flag)
{
	int	num_len;

	num_len = 0;
	if (flag.hash && !uppercase && n != 0)
		write(1, "0x", 2);
	if (flag.hash && uppercase && n != 0)
		write(1, "0X", 2);
	num_len = ft_calculate_length_hex(n, &flag);
	while (flag.isprecision && num_len < flag.precision)
	{
		ft_putchar('0');
		num_len++;
	}
	if (n != 0 || !flag.isprecision)
		ft_puthex(n, uppercase, flag);
	while (flag.iswidth && num_len < flag.width)
	{
		ft_putchar(' ');
		num_len++;
	}
	if (flag.hash)
		num_len += 2;
	return (num_len);
}

int	ft_calculate_total_length(unsigned int n, struct s_flags flag)
{
	int	num_len;
	int	tot_len;

	num_len = ft_calculate_length_hex(n, &flag);
	tot_len = num_len;
	if (flag.precision > num_len)
		tot_len = flag.precision;
	return (tot_len);
}
