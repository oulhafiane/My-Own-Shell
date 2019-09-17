/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addjob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 17:49:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/14 19:59:00 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobcontrol.h"

int		ft_newid(void)
{
	int id;

	id = 1;
	while (ft_getjob_byindex(id))
		id++;
	return (id);
}

void	ft_addjob(t_job *job, t_container *container)
{
	t_list		*list;

	list = container->list;
	if (ft_getbypgid(list, job->pgid))
		return ;
	ft_lstadd(&container->list, ft_lstnew(job, 0));
	ft_sort(container->list);
	list = container->list;
}

t_job	*ft_newjob(t_token *token, pid_t pid, char *cmd, char wait)
{
	t_job	*job;
	char	forgrounded;

	forgrounded = 1;
	while (token)
	{
		if (!token->next && token->tok_type & 64)
			forgrounded = 0;
		token = token->next;
	}
	signal(SIGCHLD, SIG_DFL);
	job = malloc(sizeof(t_job));
	job->pids = NULL;
	setpgid(pid, pid);
	job->pgid = pid;
	job->suspended = 0;
	job->foreground = forgrounded;
	job->notified = 1;
	job->pids = NULL;
	job->killed = 0;
	job->id = ft_newid();
	job->cmd = ft_strdup(cmd);
	ft_addprocess(&job, pid, wait);
	ft_jobgetter(job, 0);
	return (job);
}
