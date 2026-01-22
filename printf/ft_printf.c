/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:57:27 by ahoummad          #+#    #+#             */
/*   Updated: 2024/12/06 14:50:08 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int				count;
	va_list			args;
	struct s_flags	flag;

	flag = (struct s_flags){0};
	count = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	count += ft_start(format++, args, flag, count);
	va_end(args);
	return (count);
}
