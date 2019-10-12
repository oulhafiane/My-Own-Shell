/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 09:10:06 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/24 10:13:08 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtok(char *str, const char *delim)
{
	static char *string = 0;

	if (str)
		string = str;
	else if (!string)
		return (0);
	str = string + ft_strspn(string, delim);
	string = str + ft_strcspn(str, delim);
	if (string == str)
		return (string = 0);
	if (*string)
	{
		*string = 0;
		string += 1;
	}
	else
		string = 0;
	return (str);
}
