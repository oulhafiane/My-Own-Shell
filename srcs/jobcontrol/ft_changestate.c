/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_changestate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 21:51:22 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/02 14:16:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

int		ft_stoped(t_job *job)
{
	t_list		*lst;
	t_proc		*proc;

	lst = job->pids;
	while (lst)
	{
		proc = lst->content;
		if (!proc->stoped && !proc->exited)
			return (0);
		lst = lst->next;
	}
	job->suspended = 1;
	return (1);
}

int		ft_terminated(t_job *job)
{
	t_list		*lst;
	t_proc		*proc;

	lst = job->pids;
	while (lst)
	{
		proc = lst->content;
		if (!proc->exited)
			return (0);
		lst = lst->next;
	}
	job->killed = 1;
	return (1);
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
