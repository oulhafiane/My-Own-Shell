/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:33:07 by amoutik           #+#    #+#             */
/*   Updated: 2018/10/06 17:05:09 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	char		*string;
	size_t		i;

	if ((string = (char *)malloc(size + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i <= size + 1)
		string[i++] = '\0';
	return (string);
}
