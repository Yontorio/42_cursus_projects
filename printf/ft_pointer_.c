/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:04:15 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/06 16:07:06 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_len(unsigned int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

int	ft_pointer_len(void *ptr)
{
	unsigned long	addr;
	int				len;

	addr = (unsigned long)ptr;
	len = 0;
	if (addr == 0)
		return (5);
	while (addr != 0)
	{
		len++;
		addr /= 16;
	}
	return (len);
}

int	ft_puthexptr(unsigned long n, int uppercase, struct s_flags flag)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_puthexptr(n / 16, uppercase, flag);
	if (n % 16 < 10)
		count += ft_putchar(n % 16 + '0');
	else
		count += ft_putchar((n % 16) - 10 + 'a');
	return (count);
}

int	ft_putpointer(void *ptr, struct s_flags flag)
{
	int				count;
	unsigned long	address;

	count = 0;
	if (!ptr)
		count += write(1, "(nil)", 5);
	else
	{
		address = (unsigned long)ptr;
		if (!(flag.isprecision) && !flag.zero && ptr)
			count += write(1, "0x", 2);
		count += ft_puthexptr(address, 0, flag);
	}
	return (count);
}

int	ft_minus_padding(void *ptr, struct s_flags flag)
{
	int	num_len;
	int	count;
	int	width;

	count = 0;
	width = flag.width;
	num_len = ft_pointer_len(ptr);
	if ((flag.isprecision || flag.zero) && ptr)
		count += write(1, "0x", 2);
	while (flag.isprecision && num_len < flag.precision)
	{
		ft_putchar('0');
		num_len++;
		count++;
	}
	count += ft_putpointer(ptr, flag);
	if (ptr)
		width -= 2;
	while (flag.iswidth && num_len < width)
	{
		ft_putchar(' ');
		num_len++;
		count++;
	}
	return (count);
}
