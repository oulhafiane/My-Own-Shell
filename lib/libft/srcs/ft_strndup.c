/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 08:32:32 by amoutik           #+#    #+#             */
/*   Updated: 2019/03/11 09:23:18 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	char	*string;
	size_t	len;

	string = NULL;
	if (s1 && (len = ft_strlen(s1)))
		if ((string = (char *)malloc(sizeof(char) * len + 1)) == NULL)
			return (NULL);
	ft_strncat(string, (char *)s1, n);
	return (string);
}
