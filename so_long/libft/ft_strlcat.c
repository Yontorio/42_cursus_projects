/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:34:59 by ahoummad          #+#    #+#             */
/*   Updated: 2024/10/30 17:22:29 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	src_len = ft_strlen(src);
	if (!dst && size == 0)
		return (src_len);
	j = ft_strlen(dst);
	dst_len = j;
	if (size <= j)
		return (size + src_len);
	i = 0;
	while (src[i] && j + 1 < size)
		dst[j++] = src[i++];
	dst[j] = 0;
	return (dst_len + src_len);
}
