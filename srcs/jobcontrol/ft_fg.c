/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:01:02 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/17 19:42:01 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

void	ft_resetstatus(t_job *job)
{
	t_list	*lst;
	t_proc	*proc;

	job->suspended = 0;
	job->foreground = 1;
	lst = job->pids;
	while (lst)
	{
		proc = lst->content;
		proc->stoped = 0;
		proc->signaled = 0;
		proc->status = 0;
		lst = lst->next;
	}
}

void	ft_fg(char **arg)
{
	t_job	*job;

	if (!(job = ft_getjob(arg, "fg")))
		return ;
	tcsetpgrp(0, job->pgid);
	ft_resetstatus(job);
	signal(SIGCHLD, SIG_DFL);
	if (!killpg(job->pgid, SIGCONT))
	{
		ft_printf("[%d]\t+\t continued %s\n", job->id, job->cmd);
		ft_wait(job);
	}
	else
	{
		ft_printf("unable to continue job %s\n", job->cmd);
		ft_deljob(job, ft_getset(NULL));
	}
}
