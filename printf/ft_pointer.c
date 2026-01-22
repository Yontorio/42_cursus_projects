/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:57:33 by ahoummad          #+#    #+#             */
/*   Updated: 2024/11/29 23:26:25 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_padding(int *num_len, struct s_flags flag, int tot_len)
{
	int	count;

	count = 0;
	while (tot_len < flag.width)
	{
		if (flag.zero && !flag.isprecision)
			count += ft_putchar('0');
		else
			count += ft_putchar(' ');
		tot_len++;
		(*num_len)++;
	}
	return (count);
}

static int	write_zeros(int *zero_len, int *num_len)
{
	int	count;

	count = 0;
	while (*zero_len > 0)
	{
		count += ft_putchar('0');
		(*zero_len)--;
		(*num_len)++;
	}
	return (count);
}

static int	write_prefix(void *ptr, struct s_flags flag, int *num_len)
{
	if (flag.zero && flag.iswidth && ptr)
	{
		write(1, "0x", 2);
		num_len += 2;
		return (2);
	}
	return (0);
}

static int	ft_regular_padding(void *ptr, struct s_flags flag, int num_len)
{
	int	tot_len;
	int	zero_len;
	int	count;

	count = 0;
	tot_len = 0;
	zero_len = 0;
	if (flag.precision > num_len)
		tot_len = flag.precision + 2;
	else
		tot_len = num_len + 2;
	zero_len = flag.precision - num_len;
	if (!ptr)
		tot_len -= 2;
	count += write_prefix(ptr, flag, &num_len);
	count += write_padding(&num_len, flag, tot_len);
	if (flag.isprecision && !flag.zero && ptr)
	{
		count += write(1, "0x", 2);
		num_len += 2;
	}
	count += write_zeros(&zero_len, &num_len);
	return (count);
}

int	ft_pointer(void *ptr, struct s_flags flag)
{
	int	num_len;

	num_len = 0;
	if ((!flag.iswidth && !flag.isprecision))
		num_len = ft_putpointer(ptr, flag);
	else if (flag.minus)
		num_len = ft_minus_padding(ptr, flag);
	else
	{
		num_len = ft_pointer_len(ptr);
		num_len = ft_regular_padding(ptr, flag, num_len);
		num_len += ft_putpointer(ptr, flag);
	}
	return (num_len);
}
