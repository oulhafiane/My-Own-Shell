/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfdsrc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:16:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/30 12:16:17 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_getfdsrc(char **token, int type)
{
	int fdsrc;

	if (ft_isdigit(**token))
	{
		fdsrc = **token - 48;
		*token += 2;
	}
	else if (**token == '&')
	{
		fdsrc = -1;
		*token += 2;
	}
	else if (type == APPEND || type == TRUNC)
	{
		fdsrc = 1;
		(*token)++;
	}
	else
	{
		fdsrc = 0;
		(*token)++;
	}
	return (fdsrc);
}
