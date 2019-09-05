/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:02:19 by sid-bell          #+#    #+#             */
/*   Updated: 2019/08/18 15:35:05 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void		ft_jobs(void)
{
	t_container	*container;
	t_list		*list;
	t_job		*job;
	char		sign;

	container = ft_getset(NULL);
	ft_lstrev(&container->list);
	list = container->list;
	while (list)
	{
		job = list->content;
		sign = ' ';
		sign = job == container->current ? '+' : 0;
		sign = job == container->last ? '-' : sign;
		ft_printf("[%d]\t%c\t%d\t%s\t%s\n", job->id, sign,
			job->pgid,
			job->suspended ? "suspended" : "running",
			job->cmd);
		list = list->next;
	}
	ft_lstrev(&container->list);
}
