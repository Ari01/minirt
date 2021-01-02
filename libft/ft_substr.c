/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:33:21 by user42            #+#    #+#             */
/*   Updated: 2021/01/02 16:01:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (len + 1 <= 0)
		len = 0;
	sub = malloc(sizeof(*sub) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (i < len && s[start])
		{
			sub[i] = s[start];
			start++;
			i++;
		}
	}
	sub[i] = 0;
	return (sub);
}
