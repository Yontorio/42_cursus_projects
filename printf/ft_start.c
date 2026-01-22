/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:51:55 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/06 15:44:54 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_else(const char *format, struct s_flags flag)
{
	int	count;

	count = 0;
	count += ft_putchar('%');
	if (flag.hash == 1)
		count += ft_putchar('#');
	if (flag.plus == 1)
		count += ft_putchar('+');
	if (flag.minus == 1)
		count += ft_putchar('-');
	if (flag.width > 0)
		count += ft_recursive_putnbr(flag.width);
	if (flag.isprecision == 1)
	{
		count += ft_putchar('.');
		count += ft_recursive_putnbr(flag.precision);
	}
	count += ft_putchar(*format);
	return (count);
}

static int	pick_format(const char *format, va_list args, struct s_flags flag)
{
	int	count;

	count = 0;
	if (*format == 'd' || *format == 'i')
		count += ft_integer(va_arg(args, int), flag);
	else if (*format == 'u')
		count += ft_unsigned(va_arg(args, unsigned int), flag);
	else if (*format == 'x')
		count += ft_hexa(va_arg(args, unsigned int), 0, flag);
	else if (*format == 'X')
		count += ft_hexa(va_arg(args, unsigned int), 1, flag);
	else if (*format == 's')
		count += ft_string(format, va_arg(args, char *), flag);
	else if (*format == 'c')
		count += ft_char(va_arg(args, int), flag);
	else if (*format == 'p')
		count += ft_pointer(va_arg(args, void *), flag);
	else if (*format == '%')
		count += ft_putchar('%');
	else
		count += ft_else(format, flag);
	return (count);
}

static const char	*width_calc(const char *format, struct s_flags *flag)
{
	while (*format >= '0' && *format <= '9')
	{
		flag->iswidth = 1;
		flag->width = flag->width * 10 + (*format - '0');
		format++;
	}
	if (*format == '.')
	{
		format++;
		flag->isprecision = 1;
		flag->precision = 0;
		while (*format >= '0' && *format <= '9')
		{
			flag->precision = flag->precision * 10 + (*format - '0');
			format++;
		}
	}
	return (format);
}

static const char	*pick_flags(const char *format, struct s_flags *flag)
{
	while (*format == '-' || *format == '#' || *format == ' ' || *format == '+'
		|| *format == '0')
	{
		if (*format == '-')
			flag->minus = 1;
		else if (*format == '+')
			flag->plus = 1;
		else if (*format == '#')
			flag->hash = 1;
		else if (*format == ' ')
			flag->space = 1;
		else if (*format == '0')
			flag->zero = 1;
		format++;
	}
	if (flag->plus == 1)
		flag->space = 0;
	format = width_calc(format, flag);
	return (format);
}

int	ft_start(const char *format, va_list args, struct s_flags flag, int count)
{
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				return (count);
			flag = (struct s_flags){0};
			format = pick_flags(format, &flag);
			count += pick_format(format, args, flag);
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	return (count);
}
