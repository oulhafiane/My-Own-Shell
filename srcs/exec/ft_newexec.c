/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newexec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:05:30 by sid-bell          #+#    #+#             */
/*   Updated: 2019/10/16 21:55:54 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/resource.h>

int		ft_pipe(t_params *p, int *pipefd, t_list *lst, t_command *cmd)
{
	pipefd[0] = -1;
	pipefd[1] = -1;

	ft_restorestd(0, 1, 1, p->fd);
	if (lst->next || cmd->heredoc)
	{
		pipe(pipefd);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	return (pipefd[0]);
}

int		ft_heredoc(t_command *cmd)
{
	if (cmd->heredoc)
	{
		ft_printf_fd(1, "%s\n", cmd->heredoc);
		free(cmd->heredoc);
		cmd->heredoc = NULL;
		return (1);
	}
	return (0);
}

char	ft_init_run(t_params *params, t_command *cmd)
{
	t_builtin	*blt;

	if ((blt = ft_is_builtin(cmd->argv[0], ft_getset(0)->builtins)))
	{
		if (params->forkforbuiltin)
			ft_fork(params, NULL, cmd, blt);
		else
			run_builtin(params, blt->f, cmd->argv, params->tokens);
	}
	else if (ft_isintern(cmd->argv[0]))
		return (ft_getinterns(params, cmd));
	else
		return (ft_run(params, cmd));
	return (1);
}

void	ft_exec_job(t_params *params, t_list *lst)
{
	t_command	*cmd;
	int			fds[2];
	char		status;

	fds[0] = dup(0);
	status = 1;
	while (lst)
	{
		cmd = lst->content;
		dup2(fds[0], 0);
		close(fds[0]);
		params->pipe_stdin = ft_pipe(params, fds, lst, cmd);
		if (cmd->heredoc || ft_redirect(params->fd, cmd->redirections))
		{
			if (ft_heredoc(cmd))
				continue ;
			if (cmd->argv && cmd->argv[0])
				status = ft_init_run(params, cmd);
		}
		else
			status = 0;
		lst = lst->next;
	}
	ft_restorestd(1, 1, 1, params->fd);
	status ? 0 : ft_runnext(params->tokens, 1);
}
