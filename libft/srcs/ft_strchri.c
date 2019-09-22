/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoulhafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 01:02:02 by zoulhafi          #+#    #+#             */
/*   Updated: 2019/09/22 04:37:57 by zoulhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchri(const char *s, int c)
{
	int		i;

	if (s == NULL)
		return (0);
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == c)
			return (i);;
	}
	if (c == '\0')
		return (i);
	else
		return (0);
}
