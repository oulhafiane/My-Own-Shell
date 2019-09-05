/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <idbellasaid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 23:03:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/04 18:22:00 by sid-bell         ###   ########.fr       */
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
		if (proc->wait && !proc->stoped && !proc->exited)
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
		if (proc->wait && !proc->exited)
			return (0);
		lst = lst->next;
	}
	job->killed = 1;
	return (1);
}

void	ft_check_job(t_job *job, t_job *current, t_container *container)
{
	int			status;
	char		*st;
	t_proc		*proc;

	st = NULL;
	if (!job)
		return;
	
	proc = job->pids->content;
	status = proc->status;
	if (job->notified)
		return ;
	if (ft_terminated(job))
	{
		if (job != current || WIFSIGNALED(status))
			st = ft_join("[%d] + %s %s\n", job->id, ft_strsignal(WTERMSIG(status)), job->cmd);
	}
	else if (!job->killed && ft_stoped(job))
	{
		st = ft_join("[%d] + suspended %s\n", job->id, job->cmd);
		ft_addjob(job, container);
		if (job == current)
			container->current = job;
	}
	if (st)
		ft_lstadd(&container->notify, ft_lstnew(st, 0));
	job->notified = 1;
	if (job->killed)
		ft_deljob(job, container);
}

void	ft_check_jobs_status(t_job *current)
{
	t_list		*list;
	t_job		*job;
	t_container	*container;

	container = ft_getset(NULL);
	if (current)
		ft_check_job(current, current, container);
	list = container->list;
	while (list)
	{
		job = list->content;
		ft_check_job(job, current, container);
		list = list->next;
	}
}

void	ft_sigchld(int sig)
{
	int		status;
	pid_t	pid;

	while (sig == SIGCHLD)
	{
		if ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
			ft_change_state(NULL, pid, status);
		else
			break ;
	}
	ft_check_jobs_status(NULL);
}

void ft_notify(void)
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
