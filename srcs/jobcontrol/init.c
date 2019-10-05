/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:48:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/04 15:58:43 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

t_container	*ft_getset(t_container *container)
{
	static	t_container *c;

	if (container)
		c = container;
	return (c);
}

void		ft_init_jobcontrol(void)
{
	t_container		*container;
	pid_t			pid;
	pid_t			pgid;

	pid = getpid();
	while (1)
	{
		pgid = tcgetpgrp(0);
		if (pgid == pid)
			break ;
		kill(pid, SIGTTIN);
	}
	container = malloc(sizeof(t_container));
	container->list = NULL;
	container->current = NULL;
	container->notify = NULL;
	container->last = NULL;
	container->last_aliases = NULL;
	container->last_status = 0;
	container->interractive = 1;
	container->time_to_exit = 1;
	tcgetattr(0, &container->term);
	ft_getset(container);
	ft_ignore_signlas();
}

void		ft_handle_jobs(t_token_list *token, pid_t pid)
{
	t_job		*job;
	t_stat		st;

	ft_bzero(&st, sizeof(t_stat));
	job = ft_jobgetter(NULL, GET_JOB);
	if (!job)
		job = ft_newjob(token, pid);
	else
		ft_addprocess(&job, pid);
}

void		ft_jobs_in_child(void)
{
	t_job		*job;

	job = ft_jobgetter(NULL, GET_JOB);
	if (job)
		setpgid(getpid(), job->pgid);
	else
		setpgid(getpid(), getpid());
	ft_resetsignals();
}
