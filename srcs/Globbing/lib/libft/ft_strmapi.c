/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:01:40 by amoutik           #+#    #+#             */
/*   Updated: 2018/10/06 17:28:24 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*string;
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = ft_strlen((char *)s);
	if (!s || !f)
		return (NULL);
	if ((string = (char *)malloc(sizeof(char ) * size + 1)) == NULL)
		return (NULL);
	while (*s && i < size)
	{
		string[i] = f(i, *s);
		s++;
		i++;
	}
	string[i] = '\0';
	return (string);
}
