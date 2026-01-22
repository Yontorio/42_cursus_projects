/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:29:21 by ahoummad          #+#    #+#             */
/*   Updated: 2024/10/28 21:08:44 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	l;

	l = 0;
	if (size > 0)
	{
		while (*src && l < size - 1)
		{
			*dst++ = *src++;
			l++;
		}
		*dst = '\0';
	}
	while (*src++)
		l++;
	return (l);
}
