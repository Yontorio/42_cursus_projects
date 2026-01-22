/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:51:18 by ahoummad          #+#    #+#             */
/*   Updated: 2024/10/27 17:58:14 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_length(int n)
{
	size_t	length;

	if (n <= 0)
		length = 1;
	if (n > 0)
		length = 0;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	length;

	length = calc_length(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(length + 1);
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[--length] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
