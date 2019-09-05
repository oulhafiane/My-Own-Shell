/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_changestate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <idbellasaid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 21:51:22 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/04 17:46:00 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

t_job	*ft_pid_lookup(pid_t pid, t_proc **procc)
{
	t_list	*list;
	t_proc	*proc;
	t_list	*pids;

	list = ft_getset(NULL)->list;
	while (list)
	{
		pids = ((t_job *)list->content)->pids;
		while (pids)
		{
			proc = pids->content;
			if (proc->pid == pid)
			{
				*procc = proc;
				return (list->content);
			}
			pids = pids->next;
		}
	}
	return (NULL);
}

void	ft_getstat(t_proc *proc, int status)
{
	proc->status = status;
	proc->signaled = WIFSIGNALED(status);
	proc->stoped = WIFSTOPPED(status);
	proc->exited = !proc->stoped;
}

void	ft_change_state(t_job *job, pid_t pid, int status)
{
	pid_t	pgid;
	t_proc	*proc;

	if (job && (proc = ft_getproc_byjob(job, pid)))
	{
		ft_getstat(proc, status);
		if (proc->signaled && !job->pids->next)
			ft_print_termsig(proc->status, job->cmd);
	}
	else
	{
		proc = NULL;
		pgid = getpgid(pid);
		if (pgid == -1)
			job = ft_pid_lookup(pid, &proc);
		else
		{
			job = ft_getbypgid(ft_getset(NULL)->list, pgid);
			proc = ft_getproc_byjob(job, pid);
		}
		if (proc)
			ft_getstat(proc, status);
	}
	if (job)
		job->notified = 0;
}
