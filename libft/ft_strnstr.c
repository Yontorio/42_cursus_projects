/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:49:51 by ahoummad          #+#    #+#             */
/*   Updated: 2024/10/30 00:17:12 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack && !len)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] && haystack[i + j] && i
			+ j < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// {
// 	size_t	len_n;
// 	size_t	i;
// 	size_t	j;

// 	if (!haystack || !needle)
// 		return (NULL);
// 	if (ft_strlen(needle) == 0)
// 		return ((char *) haystack);
// 	len_n = ft_strlen(needle);
// 	i = 0;
// 	while (haystack[i] && i < len)
// 	{
// 		j = 0;
// 		while (haystack[i + j] && haystack[i + j] == needle[j] && i + j < len)
// 			j++;
// 		if (j == len_n)
// 			return ((char *) haystack + i);
// 		i++;
// 	}
// 	return (NULL);
// }
