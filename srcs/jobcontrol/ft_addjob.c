/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addjob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 17:49:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/09/20 00:29:57 by sid-bell         ###   ########.fr       */
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

void	ft_exec_mode(t_token *token, char *forgrounded)
{
	while (token)
	{
		if (token->tok_type & SH_IMPER)
			*forgrounded = 0;
		if (token->tok_type & SH_SEMI)
			break ;
		token = token->next;
	}
}

void	ft_jobname(t_job *job, t_token *token)
{
	char	*tmp;

	job->cmd = ft_strdup(token->token);
	while (token->next)
	{
		token = token->next;
		if (token->tok_type & SH_IMPER || token->tok_type & SH_SEMI)
			break ;
		tmp = job->cmd;
		job->cmd = ft_join("%s %s\n", job->cmd, token->token);
		free(tmp);
	}
}

t_job	*ft_newjob(t_token *token, pid_t pid, char wait)
{
	t_job	*job;
	char	forgrounded;

	forgrounded = 1;
	ft_exec_mode(token, &forgrounded);
	signal(SIGCHLD, SIG_DFL);
	job = malloc(sizeof(t_job));
	job->pids = NULL;
	setpgid(pid, pid);
	job->pgid = pid;
	job->suspended = 0;
	job->foreground = forgrounded;
	job->pids = NULL;
	job->killed = 0;
	job->notified = 1;
	job->id = ft_newid();
	ft_jobname(job, token);
	ft_addprocess(&job, pid, wait);
	ft_jobgetter(job, 0);
	return (job);
}
