/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:07:17 by user42            #+#    #+#             */
/*   Updated: 2020/12/27 12:02:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		is_in_charset(char c, char *separator_set)
{
	while (*separator_set)
	{
		if (c == *separator_set)
			return (1);
		separator_set++;
	}
	return (0);
}

static size_t	get_word_start(char const *s, int start, char *separator_set)
{
	while (s[start] && is_in_charset(s[start], separator_set))
		start++;
	return (start);
}

static size_t	get_word_len(char const *s, int start, char *separator_set)
{
	size_t end;

	end = start;
	while (s[end] && !is_in_charset(s[end], separator_set))
		end++;
	return (end - start);
}

static size_t	get_nwords(char const *s, char *separator_set)
{
	size_t start;
	size_t len;
	size_t nwords;

	start = 0;
	len = 0;
	nwords = 0;
	if (!s || !*s)
		return (0);
	while (s[start])
	{
		start = get_word_start(s, start, separator_set);
		len = get_word_len(s, start, separator_set);
		if (len)
			nwords++;
		start += len;
	}
	return (nwords);
}

char			**ft_split(char const *s, char *separator_set)
{
	char	**split;
	int		i;
	size_t	start;
	size_t	len;

	i = 0;
	start = 0;
	len = 0;
	if (!(split = malloc(sizeof(*split) * (get_nwords(s, separator_set) + 1))))
		return (NULL);
	if (s)
	{
		while (s[start])
		{
			start = get_word_start(s, start, separator_set);
			if ((len = get_word_len(s, start, separator_set)))
			{
				split[i] = ft_substr(s, start, len);
				i++;
			}
			start += len;
		}
	}
	split[i] = 0;
	return (split);
}
