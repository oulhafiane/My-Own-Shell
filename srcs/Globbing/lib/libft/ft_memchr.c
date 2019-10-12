/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 10:10:45 by amoutik           #+#    #+#             */
/*   Updated: 2018/10/08 12:10:56 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*big;

	big = (unsigned char *)s;
	while (n--)
		if (*big != (unsigned char)c)
			big++;
		else
			return (big);
	return (0);
}
