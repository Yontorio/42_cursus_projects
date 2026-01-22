/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:57:35 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/01 17:39:58 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

static int	ft_calculate_length(const char *format, char *s)
{
	int	num_len;

	num_len = 0;
	if (*format == 's')
	{
		if (s == NULL)
			num_len = 6;
		else
			num_len = ft_strlen(s);
	}
	return (num_len);
}

static int	ft_putstr(char *s, struct s_flags flag)
{
	int	count;
	int	len;

	count = 0;
	if (s == NULL)
	{
		if (flag.isprecision && flag.precision < 6)
			return (count);
		count += ft_putstr("(null)", flag);
		return (count);
	}
	len = ft_strlen(s);
	if (flag.isprecision)
	{
		if (flag.precision < len)
			len = flag.precision;
	}
	while (*s && len--)
		count += ft_putchar(*s++);
	return (count);
}

static int	ft_handle_string_padding(const char *format, char *s,
		struct s_flags flag, int num_len)
{
	if (flag.minus)
	{
		num_len = ft_putstr(s, flag);
		while (num_len < flag.width)
		{
			ft_putchar(' ');
			num_len++;
		}
	}
	else
	{
		num_len = ft_calculate_length(format, s);
		if (s && flag.isprecision && flag.precision < num_len)
			num_len = flag.precision;
		else if (!s && flag.isprecision && flag.precision < num_len)
			num_len = 0;
		while (num_len < flag.width)
		{
			ft_putchar(' ');
			num_len++;
		}
		ft_putstr(s, flag);
	}
	return (num_len);
}

int	ft_string(const char *format, char *s, struct s_flags flag)
{
	int	num_len;

	num_len = 0;
	if (!flag.iswidth && !flag.isprecision)
		num_len = ft_putstr(s, flag);
	else
		num_len = ft_handle_string_padding(format, s, flag, num_len);
	return (num_len);
}
