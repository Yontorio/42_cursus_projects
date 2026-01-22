/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahoummad <ahoummad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:05:56 by ahoummad          #+#    #+#             */
/*   Updated: 2025/03/20 20:18:29 by ahoummad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[n] = '\0';
	return (dup);
}

static void	cleanup(char **result, int i)
{
	while (i-- > 0)
		free(result[i]);
	free(result);
}

char	*get_next_word(const char **s, char c)
{
	int		word_len;
	char	*word;

	word_len = 0;
	while (**s == c)
		(*s)++;
	while ((*s)[word_len] && (*s)[word_len] != c)
		word_len++;
	if (word_len == 0)
		return (NULL);
	word = strndup(*s, word_len);
	*s += word_len;
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s && i < word_count)
	{
		result[i] = get_next_word(&s, c);
		if (!result[i])
			return (cleanup(result, i), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}
