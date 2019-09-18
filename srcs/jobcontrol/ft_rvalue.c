/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rvalue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:03:21 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/18 16:04:49 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_set_last_rvalue(int rvalue)
{
	t_container *container;

	container = ft_getset(NULL);
	container->last_status = rvalue;
}

int		ft_get_last_rvalue(void)
{
	t_container *container;

	container = ft_getset(NULL);
	return (container->last_status);
}
