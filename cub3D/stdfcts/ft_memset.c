/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:37:58 by ahoummad          #+#    #+#             */
/*   Updated: 2026/01/10 19:40:05 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdfcts.h"

void	*ft_memset(void *str, int c, size_t l)
{
	void			*s;
	size_t			r;
	unsigned char	x;

	s = str;
	x = (unsigned char) c;
	r = 0x0101010101010101 * x;
	while (l && (l % 8 != 0))
	{
		*((char *) s++) = x;
		l--;
	}
	while (l >= sizeof(size_t))
	{
		*((size_t *) s) = r;
		l -= sizeof(size_t);
		s += sizeof(size_t);
	}
	while (l)
	{
		*((char *) s++) = x;
		l--;
	}
	return (str);
}
