/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:46:13 by amoutik           #+#    #+#             */
/*   Updated: 2018/10/06 17:16:47 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*string;
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = ft_strlen((char *)s);
	if (!s || !f)
		return (NULL);
	if ((string = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	while (*s && i < size)
	{
		string[i++] = f(*s);
		s++;
	}
	string[i] = '\0';
	return (string);
}
