/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettype.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:15:22 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/30 12:15:32 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_gettype(char *str)
{
	char	*ptr;

	if ((ptr = ft_strchr(str, '>')))
	{
		if (ptr[1] == '>')
			return (APPEND);
		else
			return (TRUNC);
	}
	else if (ft_strstr(str, "<<"))
		return (HERDOC);
	else
		return (O_RDONLY);
}
