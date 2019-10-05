/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 23:03:34 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/03 14:09:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

char	*ft_stopped_action(t_job *job, t_job *current, int status)
{
	t_container *container;
	char		*st;

	container = ft_getset(0);
	st = ft_join("[%d] + Stopped %s\n", job->id, job->cmd);
	ft_addjob(job, container);
	(job == current) ? container->current = job : 0;
	ft_runnext(job->tokens, WEXITSTATUS(status));
	return (st);
}

void	ft_check_job(t_job *job, t_job *current, t_container *container)
{
	int			status;
	char		*st;
	t_proc		*proc;

	if (((st = NULL) || 1) && job->notified)
		return ;
	proc = job->pids->content;
	status = proc->status;
	if (ft_terminated(job))
	{
		if (job != current || WIFSIGNALED(status))
			st = ft_join("[%d] + %s %s\n", job->id,
				ft_strsignal(WTERMSIG(status)), job->cmd);
		ft_runnext(job->tokens, WEXITSTATUS(status));
	}
	else if (!job->killed && ft_stoped(job))
		st = ft_stopped_action(job, current, status);
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
		if (job)
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
