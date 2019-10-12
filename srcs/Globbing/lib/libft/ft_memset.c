/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 08:13:17 by amoutik           #+#    #+#             */
/*   Updated: 2018/10/09 08:34:21 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *output;

	if (len == 0)
		return (b);
	output = (unsigned char *)b;
	while (len--)
	{
		*output = (unsigned char)c;
		output++;
	}
	return (b);
}
