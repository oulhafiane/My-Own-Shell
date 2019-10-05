/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addjob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 17:49:23 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/02 14:16:35 by sid-bell         ###   ########.fr       */
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
}

void	ft_exec_mode(t_token *token, char *forgrounded)
{
	*forgrounded = 1;
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
		if (token->tok_type & SH_DPIPE || token->tok_type & SH_LOGAND)
			break ;
		if (token->tok_type & SH_IMPER || token->tok_type & SH_SEMI)
			break ;
		tmp = job->cmd;
		job->cmd = ft_join("%s %s\n", job->cmd, token->token);
		free(tmp);
	}
}

t_job	*ft_newjob(t_token_list *tokens, pid_t pid)
{
	t_job	*job;
	char	forgrounded;

	ft_exec_mode(tokens->head, &forgrounded);
	job = malloc(sizeof(t_job));
	job->pids = NULL;
	setpgid(pid, pid);
	job->pgid = pid;
	job->suspended = 0;
	job->foreground = forgrounded;
	job->pids = NULL;
	job->killed = 0;
	job->notified = 1;
	job->tokens = tokens;
	job->id = ft_newid();
	ft_jobname(job, tokens->head);
	ft_addprocess(&job, pid);
	ft_jobgetter(job, 0);
	return (job);
}
