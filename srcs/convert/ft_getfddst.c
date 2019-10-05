/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfddst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:16:36 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/30 12:16:43 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_getfddst(char *token, char *next, char **file)
{
	int fddst;

	fddst = -1;
	if (!*token)
		*file = next;
	else if (*token == '&')
	{
		if (ft_isnumber(next))
			fddst = ft_atoi(next);
		else if (ft_strequ(next, "-"))
			fddst = CLOSE_FD;
		else
		{
			*file = next;
			return (-3);
		}
	}
	return (fddst);
}
