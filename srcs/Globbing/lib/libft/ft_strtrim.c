/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:32:03 by amoutik           #+#    #+#             */
/*   Updated: 2018/10/09 08:08:16 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*string;
	unsigned int	i;
	unsigned int	len;
	unsigned int	j;

	i = 0;
	len = ft_strlen((char *)s);
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '\0')
		return (ft_strnew(0));
	while (s[len - 1] && ft_isspace(s[len - 1]))
		len--;
	if ((string = (char *)malloc(sizeof(char) * (len - i + 1))) == NULL)
		return (NULL);
	j = 0;
	while (s[i] && i < len)
	{
		string[j++] = s[i++];
	}
	string[j] = '\0';
	return (string);
}
