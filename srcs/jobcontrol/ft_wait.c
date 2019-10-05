/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 03:03:26 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/28 20:32:53 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"
#include "fcntl.h"
#include <termios.h>

void	ft_get_term(t_job *job)
{
	t_container	*container;

	container = ft_getset(NULL);
	ft_check_jobs_status(job);
	if (container->interractive)
	{
		if (tcsetpgrp(0, getpid()) == -1)
		{
			ft_printf_fd(2, "42sh : fatal error");
			exit(1);
		}
		tcsetattr(0, TCSANOW, &container->term);
	}
}

void	ft_wait(t_job *job)
{
	int			status;
	pid_t		pid;

	job->suspended = 0;
	if (!job->foreground && ft_getset(0)->interractive)
	{
		ft_getset(NULL)->current = job;
		ft_addjob(job, ft_getset(NULL));
		ft_printf("[%d] %d\n", job->id, job->pgid);
	}
	else
	{
		if (ft_getset(0)->interractive)
			tcsetpgrp(0, job->pgid);
		while (1)
		{
			if ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
			{
				ft_change_state(job, pid, status);
				if (ft_terminated(job) || ft_stoped(job))
					break ;
			}
		}
		ft_get_term(job);
	}
}

void	ft_init_wait(void)
{
	t_job	*job;

	job = ft_jobgetter(NULL, GET_JOB);
	if (job)
	{
		job->killed = 0;
		ft_jobgetter(NULL, RESET);
		ft_wait(job);
	}
}
