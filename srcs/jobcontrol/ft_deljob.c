/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deljob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 02:57:49 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/28 20:24:42 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_del(t_list *prev, t_list *list, t_container *container)
{
	if (list->next)
		container->current = list->next->content;
	else if (prev)
		container->current = prev->content;
	else
		container->current = NULL;
}

void	ft_save_last_status(t_job *job)
{
	t_container *container;
	t_proc		*proc;

	container = ft_getset(NULL);
	if (job->pids)
	{
		proc = job->pids->content;
		if (proc)
			container->last_status = WEXITSTATUS(proc->status);
		else
			container->last_status = 0;
	}
	else
		container->last_status = 0;
}

void	ft_deljob(t_job *job, t_container *container)
{
	t_list		*list;
	t_job		*jb;
	t_list		*prev;

	list = container->list;
	((prev = NULL) || 1) ? ft_save_last_status(job) : 0;
	while (list)
	{
		jb = list->content;
		if (jb->pgid == job->pgid)
		{
			if (container->current && container->current->pgid == jb->pgid)
				ft_del(prev, list, container);
			if (prev)
				prev->next = list->next;
			else
				container->list = container->list->next;
			ft_free_job(jb);
			free(list);
			return ;
		}
		prev = list;
		list = list->next;
	}
	ft_free_job(job);
}
