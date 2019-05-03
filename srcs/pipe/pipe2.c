/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:17:20 by amoutik           #+#    #+#             */
/*   Updated: 2019/04/29 09:52:38 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		pipe_and_fork(int fd[2], pid_t *pid)
{
	if (pipe(fd) == -1)
		exit_shell("21sh: Error in pipe\n");
	if ((*pid = fork()) == -1)
		exit(EXIT_FAILURE);
}

void		check_ambiguous(t_redirect *redirect, int *fd_in)
{
	if (!loop_dup2(redirect->dup_head, 1))
		dup2(*fd_in, 0);
	else
		exit_shell("Ambiguous input redirect.\n");
}

int			wait_fork(t_list **cmds, int fd[2], int *fd_in, int pid)
{
	int status;

	status = 0;
	if ((*cmds)->next == NULL)
		waitpid(pid, &status, 0);
	close(fd[1]);
	*fd_in = fd[0];
	*cmds = (*cmds)->next;
	return (status);
}

void		piping(t_list *cmds, t_list **env, t_list *built_in)
{
	int			fd[2];
	int			fd_in;
	pid_t		pid;
	t_redirect	*redirect;

	fd_in = 0;
	while (cmds != NULL)
	{
		pipe_and_fork(fd, &pid);
		if (pid == 0)
		{
			redirect = (t_redirect *)cmds->content;
			check_ambiguous(redirect, &fd_in);
			if (cmds->next != NULL)
				dup2(fd[1], 1);
			loop_dup(redirect->dup_head, 1);
			close(fd[0]);
			execute_command(&redirect->command, env, built_in);
		}
		else if (pid > 0)
			if (wait_fork(&cmds, fd, &fd_in, pid))
				break ;
	}
}