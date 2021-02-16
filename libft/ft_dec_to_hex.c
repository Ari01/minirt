/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_to_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:29:45 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 10:32:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_dec_to_hex(int d)
{
	char	*base;
	char	*res;
	int		len;
	int		tmp;

	base = "0123456789abcdef";
	len = 1;
	tmp = d;
	while ((tmp = tmp / 16))
		len++;
	res = malloc(sizeof(*res) * (len + 1));
	res[len] = 0;
	tmp = len - 1;
	while (tmp >= 0)
	{
		res[tmp] = base[d % 16];
		d = d / 16;
		tmp--;
	}
	return (res);
}
