/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:45:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/17 19:45:24 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_notify(void)
{
	t_list		*list;
	t_list		*tmp;
	t_container	*container;

	container = ft_getset(NULL);
	list = container->notify;
	while (list)
	{
		ft_printf("%s", list->content);
		tmp = list;
		free(list->content);
		list = list->next;
		free(tmp);
	}
	container->notify = NULL;
}
